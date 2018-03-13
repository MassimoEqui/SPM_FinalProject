#include "include/parallel_genetics/ParallelForest.h"

#include<cstdlib>
#include<cmath>
#include<vector>

#include <ff/parallel_for.hpp>
using namespace ff;
//DEBUG
#include<iostream>
#include<iomanip>

ParallelForest::ParallelForest(int treeNum, int depthmax, int randmax, int randseed, int nw_farm, int nw_parallelFor){
    if(treeNum < 0)
        return;
    std::srand(randseed);
    this->treePool = new std::pair<ParallelTree*, double>[treeNum];
    this->treeNum = treeNum;
    this->depthmax = depthmax;
    this->nw_farm = nw_farm;
    this->nw_parallelFor = nw_parallelFor;
    this->bestTree.first = nullptr;
    this->bestTree.second = -1;
    this->fitnessUpdated = false;
    this->bestTreeUpdated = false;
    for(int i=0; i<treeNum; i++){
        this->treePool[i].first = new ParallelTree(std::rand()%(depthmax+1), randmax, std::rand());
        this->treePool[i].second = -1.0;
    }
};

ParallelForest::~ParallelForest(){
    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i].first;
    delete this->treePool;
};

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
        std::pair<ParallelTree*, double>* treePool = forest->getTreePool();
		for(int i=i_start; i<i_stop; i++)
			treePool[i].second =
                forest->fitness(treePool[i].first, this->x_vals, this->y_vals, points_no);
		return GO_ON;
	}
};

double ParallelForest::fitness(ParallelTree* f, double* x_vals, double* y_vals, int points_no){
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

void ParallelForest::updateBestTree(double* x_vals, double* y_vals, int points_no){
    if(this->bestTreeUpdated) return;

    this->updatePoolFitness(x_vals, y_vals, points_no);
    this->bestTree = this->treePool[0];
    for(int i=0; i<this->treeNum; i++){
        double new_E = this->treePool[i].second;
        double curr_E = this->bestTree.second;
        if(!std::isnan(new_E) && !std::isinf(new_E)){
            if(std::isnan(curr_E) || std::isinf(curr_E) || new_E < curr_E)
                this->bestTree = this->treePool[i];
        } 
    }
    this->bestTreeUpdated = true;
};

int* ParallelForest::selectBests(double* x_vals, double* y_vals, int points_no, int threshold){
    if(threshold > this->treeNum) return nullptr;

    this->updatePoolFitness(x_vals, y_vals, points_no);

    int* bestTrees_idx = new int[threshold];
    double bestTrees_E[threshold];

    bool full = false;
    int j = 0;
    for(int i=0; i<this->treeNum; i++){
        int maxE_idx = -1;
        double E = this->treePool[i].second;

        double maxE = E;
        if(!full){
            bestTrees_idx[j] = i;
            bestTrees_E[j] = E;
            j++;
            if(j == threshold)
                full = true;
        }
        else if(!std::isnan(E) && !std::isinf(E)){
            j = 0;
            bool done = false;
            while(!done && j<threshold){
                if(bestTrees_E[j]>maxE ||
                    std::isnan(bestTrees_E[j]) || std::isinf(bestTrees_E[j])){
                    maxE = bestTrees_E[j];
                    maxE_idx = j;
                }
                j++;
            }
        }

        if(maxE_idx >= 0){
            bestTrees_idx[maxE_idx] = i;
            bestTrees_E[maxE_idx] = E;
        }
    }
    return bestTrees_idx;
};

ParallelTree* ParallelForest::crossover(int tree1_id, int tree2_id){
    if(tree1_id < 0 || tree1_id > this->treeNum ||
        tree2_id < 0 || tree2_id > this->treeNum ||
            tree1_id == tree2_id)
        return nullptr;
    
    //Get the trees
    ParallelTree* tree_1 = this->treePool[tree1_id].first->copy();
    ParallelTree* tree_2 = this->treePool[tree2_id].first->copy();
    int t1_depth = tree_1->getDepth();
    int t2_depth = tree_2->getDepth();
    int height = std::rand() % (std::min(t1_depth, t2_depth) + 1);

    //Basic cases
    if(height > t1_depth || height > t2_depth)
        return tree_1;
    
    if(height == t1_depth && height == t2_depth){
        tree_1->setRoot((Node*)tree_2->setRoot((Node*)tree_1->getRoot()));
        return tree_1;
    }

    if(height == t1_depth){
        INode* subTree_2 = tree_2->getRandomSubtree(t2_depth-height-1);
        INode** sT2_children = subTree_2->getChildren();
        int sT2_childrenNum = subTree_2->getChildrenNum();
        int child2_id = 0;
        if(sT2_childrenNum>1)
            child2_id = std::rand() % sT2_childrenNum;
        subTree_2->setChild(child2_id, tree_1->setRoot((Node*)sT2_children[child2_id]));
        return tree_1;
    }

    if(height == t2_depth){
        INode* subTree_1 = tree_1->getRandomSubtree(t1_depth-height-1);
        INode** sT1_children = subTree_1->getChildren();
        int sT1_childrenNum = subTree_1->getChildrenNum();
        int child1_id = 0;
        if(sT1_childrenNum>1)
            child1_id = std::rand() % sT1_childrenNum;
        subTree_1->setChild(child1_id, tree_2->setRoot((Node*)sT1_children[child1_id]));
        return tree_1;
    }
    
    //Get some random subtrees and their children
    INode* subTree_1 = tree_1->getRandomSubtree(t1_depth-height-1);
    INode* subTree_2 = tree_2->getRandomSubtree(t2_depth-height-1);
    INode** sT1_children = subTree_1->getChildren();
    INode** sT2_children = subTree_2->getChildren();
    int sT1_childrenNum = subTree_1->getChildrenNum();
    int sT2_childrenNum = subTree_2->getChildrenNum();
    //If a subtree has more than 1 child, choose one of them randomly
    int child1_id = 0, child2_id = 0;
    if(sT1_childrenNum>1)
        child1_id = std::rand() % sT1_childrenNum;
    if(sT2_childrenNum>1)
        child2_id = std::rand() % sT2_childrenNum;
    //Swap the choosen children
    subTree_2->setChild(child2_id,
        subTree_1->setChild(child1_id, sT2_children[child2_id]));
    return tree_1;
};

ParallelTree* ParallelForest::mutation(int tree_id){
    if(tree_id < 0)
        return nullptr;
    int depth = std::rand() % (this->treePool[tree_id].first->getDepth()+1);
    ParallelTree* newTree = this->treePool[tree_id].first->copy();
    newTree->mutation(depth);
    return newTree;
};

void ParallelForest::newGeneration(std::vector<ParallelTree*>& bestTrees){
    std::pair<ParallelTree*, double>* newTreePool = new std::pair<ParallelTree*, double>[this->treeNum];
    int bestTrees_no = bestTrees.size();
  
    for(int i=0; i<bestTrees_no; i++){
        newTreePool[i].first = bestTrees[i];
        newTreePool[i].second = -1.0;
    }

    for(int i=bestTrees_no; i<this->treeNum; i++){
        newTreePool[i].first = bestTrees[std::rand()%bestTrees_no]->copy();
        newTreePool[i].second = -1.0;
    }

    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i].first;
    delete this->treePool;

    this->treePool = newTreePool;
    this->fitnessUpdated = false;
    this->bestTreeUpdated = false;
};

std::pair<ParallelTree*, double>* ParallelForest::getTreePool(){
    return this->treePool;
}

ParallelTree* ParallelForest::getBestTree(double* x_vals, double* y_vals, int points_no){
    this->updateBestTree(x_vals, y_vals, points_no);
    return this->bestTree.first;
};

double ParallelForest::getBestFitness(double* x_vals, double* y_vals, int points_no){
    this->updateBestTree(x_vals, y_vals, points_no);
    return this->bestTree.second;
};

ParallelTree* ParallelForest::getTree(int tree_id){
    if(tree_id < 0 || tree_id > this->treeNum) return nullptr;
    return this->treePool[tree_id].first;
};

std::string ParallelForest::toString(){
    std::string s = "";
    for(int i=0; i<this->treeNum; i++)
        s = s+"\n\nTree [ "+std::to_string(i)+" ]\n"+this->treePool[i].first->toString();
    s += "\n\n";
    return s;
};