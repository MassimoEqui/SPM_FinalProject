#include "include/genetics/ParallelForest.h"

#include<cstdlib>
#include<cmath>
#include<vector>

#include <ff/parallel_for.hpp>
using namespace ff;
//DEBUG
#include<iostream>
#include<iomanip>

ParallelForest::ParallelForest(int treeNum, int depthmax, int randmax, int randseed, int nw_farm, int nw_parallelFor)
    :Forest(treeNum, depthmax, randmax){
    if(treeNum < 0)
        return;
    std::srand(randseed);
    this->treePool = new std::pair<Tree*, double>[treeNum];
    this->treeNum = treeNum;
    this->depthmax = depthmax;
    this->nw_farm = nw_farm;
    this->nw_parallelFor = nw_parallelFor;
    this->bestTree.first = nullptr;
    this->bestTree.second = -1;
    this->fitnessUpdated = false;
    this->bestTreeUpdated = false;
    for(int i=0; i<treeNum; i++){
        this->treePool[i].first = new Tree(std::rand()%(depthmax+1), randmax, std::rand());
        this->treePool[i].second = -1.0;
    }
};

ParallelForest::~ParallelForest(){};

class Emitter: public ff_node {
private:
	int nw, dim;
public:
	Emitter(int nw, int dim){ this->nw = nw; this->dim = dim; };

	void* svc(void* task){
		int delta = this->dim/this->nw;
		int i;
		for(i=0; i<this->nw-1; i++)
			ff_send_out((void*)(new std::pair<int,int>(i*delta,(i+1)*delta)));
		ff_send_out((void*)(new std::pair<int,int>(i*delta,dim)));
		ff_send_out(EOS);
		return nullptr;
	}
};

class Worker: public ff_node {
private:
	ParallelForest* forest;
    double* x_vals, *y_vals;
    int points_no;
public:
	Worker(ParallelForest* forest, double* x_vals, double*y_vals, int points_no){
        this->forest = forest;
        this->x_vals = x_vals;
        this->y_vals = y_vals;
        this->points_no = points_no;
    };

	void* svc(void* task){
		int i_start = (int)(((std::pair<int,int>*)task)->first);
		int i_stop = (int)(((std::pair<int,int>*)task)->second);
        std::pair<Tree*, double>* treePool = forest->getTreePool();
		for(int i=i_start; i<i_stop; i++)
			treePool[i].second =
                forest->fitness(treePool[i].first, this->x_vals, this->y_vals, points_no);
		return GO_ON;
	}
};

double ParallelForest::fitness(Tree* f, double* x_vals, double* y_vals, int points_no){
    double E = 0.0;
    ParallelForReduce<double> pfr(this->nw_parallelFor);
    pfr.parallel_reduce(E, 0.0,
        0, points_no, 1, 0,
            [&](const long i, double& E){
                double delta = y_vals[i] - f->evaluate(x_vals[i]);
                E += delta*delta; },
            [&](double& s, const double& e){ s += e; },
    this->nw_parallelFor);

    return std::sqrt(E);
};

void ParallelForest::updatePoolFitness(double* x_vals, double* y_vals, int points_no){
    if(this->fitnessUpdated) return;

    std::vector<ff_node*> workers;
	Emitter* emitter = new Emitter(this->nw_farm, this->treeNum);
	for(int i=0; i<this->nw_farm; i++)
		workers.push_back(new Worker(this, x_vals, y_vals, points_no));
	ff_farm<> F;
	F.add_emitter(emitter);
	F.add_workers(workers);
	F.remove_collector();
	F.run_and_wait_end();
};