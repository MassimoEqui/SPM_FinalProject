#include "include/genetics/ParallelForest.h"

#include<cstdlib>
#include<cmath>
#include<vector>
#include<functional>

#include <ff/parallel_for.hpp>
using namespace ff;
//DEBUG
#include<iostream>
#include<iomanip>

ParallelForest::ParallelForest(int treeNum, int depthmax, int randmax, int nw_F, int nw_PF)
    :Forest(treeNum, depthmax, randmax){
    this->nw_F = nw_F;
    this->nw_PF = nw_PF;
};

ParallelForest::~ParallelForest(){};

class Emitter: public ff_node {
private:
	int nw, tree_no, delta;
    std::pair<Tree*, double>* treePool;

public:
	Emitter(int nw, int tree_no, std::pair<Tree*, double>* treePool){
        this->nw = nw;
        this->tree_no = tree_no;
        this->treePool = treePool;
        this->delta = tree_no/nw;
    };

	void* svc(void* task){
		int i, i_start;

		for(i=0; i<=this->nw; i++){
            i_start = i*this->delta;
            if(i == this->nw) this->delta = tree_no - i_start;
            if(this->delta >0 ){
                std::pair<Tree*, double>* partialTreePool = new std::pair<Tree*, double>[this->delta];
                for(int j=0; j<this->delta; j++){
                    partialTreePool[j] = this->treePool[i_start + j];
                }
                ff_send_out((void*)(new std::pair<int,std::pair<Tree*, double>*>(i_start,partialTreePool)));
            }
        }
		return EOS;
	};
};

class Worker: public ff_node {
private:
    std::function<double(Tree*,double*,double*,int)> fitness;
    int nw, tree_no, delta, points_no;
    double* x_vals, *y_vals;
public:
	Worker(std::function<double(Tree*,double*,double*,int)>& fitness, int nw, int tree_no, double* x_vals, double*y_vals, int points_no){
        this->fitness = fitness;
        this->nw = nw;
        this->tree_no = tree_no;
        this->delta = tree_no/nw;
        this->x_vals = x_vals;
        this->y_vals = y_vals;
        this->points_no = points_no;
    };

	void* svc(void* task){
		int i_start = (((std::pair<int,std::pair<Tree*, double>*>*)task)->first);
		std::pair<Tree*, double>* partialTreePool =
            (((std::pair<int,std::pair<Tree*, double>*>*)task)->second);
        

        if(this->tree_no - i_start < this->delta)
            this->delta = this->tree_no - i_start;
        
        for(int i=0; i<this->delta; i++){
			partialTreePool[i].second =
                this->fitness(partialTreePool[i].first, this->x_vals, this->y_vals, points_no);

            
        }

        ff_send_out((void*)(task));
        
		return GO_ON;
	};
};

class Collector: public ff_node {
private:
	int nw, tree_no, delta;
    std::pair<Tree*, double>* treePool;
    double* poolFitnesses;

public:
	Collector(int nw, int tree_no, std::pair<Tree*, double>* treePool){
        this->nw = nw;
        this->tree_no = tree_no;
        this->treePool = treePool;
        this->delta = tree_no/nw;
        this->poolFitnesses = new double[tree_no];
    };

	void* svc(void* task){
		int i_start = (int)(((std::pair<int,std::pair<Tree*, double>*>*)task)->first);
		std::pair<Tree*, double>* partialTreePool =
            (std::pair<Tree*, double>*)(((std::pair<int,std::pair<Tree*, double>*>*)task)->second);
        
        if(this->tree_no - i_start < this->delta){
            this->delta = this->tree_no - i_start;
        }
                
        for(int i = 0; i<this->delta; i++) {
            this->poolFitnesses[i_start + i] = partialTreePool[i].second;
        }
                
        delete partialTreePool;
        delete (std::pair<int,std::pair<Tree*, double>*>*)task;
        
		return GO_ON;
	};

    void svc_end(){
        for(int i=0; i<this->tree_no; i++){
            this->treePool[i].second = this->poolFitnesses[i];
        }
        delete this->poolFitnesses;
    }
};

double ParallelForest::fitness(Tree* f, double* x_vals, double* y_vals, int points_no){
    double E = 0.0;
    ParallelForReduce<double> pfr(this->nw_PF);
    pfr.parallel_reduce(E, 0.0,
        0, points_no, 1, 0,
            [&](const long i, double& E){
                double delta = y_vals[i] - f->evaluate(x_vals[i]);
                E += delta*delta; },
            [&](double& s, const double& e){ s += e; },
    this->nw_PF);

    return std::sqrt(E);
};

void ParallelForest::updatePoolFitness(double* x_vals, double* y_vals, int points_no){
    if(this->fitnessUpdated) return;

    std::vector<ff_node*> workers;
	Emitter* emitter = new Emitter(this->nw_F, this->treeNum, this->treePool);
    std::function<double(Tree*,double*,double*,int)> fit =
            [this](Tree* tree, double* x_vals, double* y_vals, int points_no)->double
                { return this->fitness(tree, x_vals, y_vals, points_no); };

	for(int i=0; i<this->nw_F; i++)       
        workers.push_back(new Worker(fit, this->nw_F, this->treeNum, x_vals, y_vals, points_no));
	ff_farm<> F;
    Collector* collector = new Collector(this->nw_F, this->treeNum, this->treePool);
	F.add_emitter(emitter);
	F.add_workers(workers);
	F.add_collector(collector);
	F.run_and_wait_end();
};