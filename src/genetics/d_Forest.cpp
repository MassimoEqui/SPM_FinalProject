#include "include/genetics/Forest.h"

#include<cstdlib>
#include<cmath>
//DEBUG
#include<iostream>
#include<iomanip>
#include<ff/parallel_for.hpp>
using namespace ff;

Forest::Forest(int treeNum, int depthmax, int threshold, int randmax, int randseed){
    if(treeNum < 0)
        return;
    std::srand(randseed);
    this->treePool = new Tree*[treeNum];
    this->treeNum = treeNum;
    this->threshold = threshold;
    this->depthmax = depthmax;
    for(int i=0; i<treeNum; i++)
        this->treePool[i] = new Tree(std::rand()%(depthmax+1), randmax, std::rand());
};

Forest::~Forest(){
    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i];
    delete this->treePool;
}

double Forest::fitness(Tree* f, double* x_vals, double* y_vals, int pointsNum){
    double E = 0.0;
    for(int i=0; i<pointsNum; i++)
        E += std::pow(y_vals[i] - f->evaluate(x_vals[i]), 2);
    
    return std::sqrt(E);
};

int* Forest::selectBests(double* x_vals, double* y_vals, int pointsNum){
    int* bestTrees_idx = new int[this->threshold];
    double bestTrees_E[this->threshold];/*
    for(int i=0; i<this->threshold; i++){
        bestTrees_idx[i] = -1;
        bestTrees_E[i] = -1.0;
    }*/

    bool full = false;
    int j = 0;
    for(int i=0; i<this->treeNum; i++){
        bool done = false;
        int maxE_idx = -1;
    ffTime(START_TIME);
        double E = this->fitness(this->treePool[i], x_vals, y_vals, pointsNum);
    ffTime(STOP_TIME);
        double maxE = E;
        if(!full){
            bestTrees_idx[j] = i;
            bestTrees_E[j] = E;
            done = true;
            j++;
            if(j == threshold)
                full = true;
        }
        else if(!std::isnan(E) && !std::isinf(E)){
            j = 0;
            while(!done && j<this->threshold){
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
    std::cout << "Time (ms) = " << std::setprecision(5) << ffTime(GET_TIME) << "\n";
    return bestTrees_idx;
};

void Forest::crossover(int tree1_id, int tree2_id){
    if(tree1_id < 0 || tree1_id > this->treeNum ||
        tree2_id < 0 || tree2_id > this->treeNum ||
            tree1_id == tree2_id)
        return;
    
    //Get the trees
    Tree* tree_1 = this->treePool[tree1_id];
    Tree* tree_2 = this->treePool[tree2_id];
    int t1_depth = tree_1->getDepth();
    int t2_depth = tree_2->getDepth();
    int height = std::rand() % (std::min(t1_depth, t2_depth) + 1);

    //Basic cases
    if(height > t1_depth || height > t2_depth)
        return;
    
    if(height == t1_depth && height == t2_depth){
        tree_1->setRoot((Node*)tree_2->setRoot((Node*)tree_1->getRoot()));
        return;
    }

    if(height == t1_depth){
        INode* subTree_2 = tree_2->getRandomSubtree(t2_depth-height-1);
        INode** sT2_children = subTree_2->getChildren();
        int sT2_childrenNum = subTree_2->getChildrenNum();
        int child2_id = 0;
        if(sT2_childrenNum>1)
            child2_id = std::rand() % sT2_childrenNum;
        subTree_2->setChild(child2_id, tree_1->setRoot((Node*)sT2_children[child2_id]));
        return;
    }

    if(height == t2_depth){
        INode* subTree_1 = tree_1->getRandomSubtree(t1_depth-height-1);
        INode** sT1_children = subTree_1->getChildren();
        int sT1_childrenNum = subTree_1->getChildrenNum();
        int child1_id = 0;
        if(sT1_childrenNum>1)
            child1_id = std::rand() % sT1_childrenNum;
        subTree_1->setChild(child1_id, tree_2->setRoot((Node*)sT1_children[child1_id]));
        return;
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
};

void Forest::mutation(int tree_id){
    if(tree_id < 0)
        return;
    int depth = std::rand() % (this->treePool[tree_id]->getDepth()+1);
    this->treePool[tree_id]->mutation(depth);
};

void Forest::newGeneration(int* bestTrees){
    Tree** newTreePool = new Tree*[this->treeNum];
    for(int i=0; i<this->threshold; i++)
        newTreePool[i] = this->treePool[bestTrees[i]]->copy();  
    for(int i=threshold; i<this->treeNum; i++)
        newTreePool[i] = this->treePool[bestTrees[std::rand()%this->threshold]]->copy();
    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i];
    delete this->treePool;
    this->treePool = newTreePool;
}

Tree* Forest::getBest(double* x_vals, double* y_vals, int pointsNum){
    if(this->treeNum<=0)
        return nullptr;

    int bestTree_id = 0;
    double E = this->fitness(this->treePool[bestTree_id], x_vals, y_vals, pointsNum);
    double bestE = E;
    for(int i=1; i<this->treeNum; i++){
        double E = this->fitness(this->treePool[i], x_vals, y_vals, pointsNum);
        if(!std::isnan(E) && !std::isinf(E)){
            if(E < bestE || std::isnan(bestE) || std::isinf(bestE)){
                bestE = E;
                bestTree_id = i;
            }
        }
    }

    return this->treePool[bestTree_id];
}

std::string Forest::toString(){
    std::string s = "";
    for(int i=0; i<this->treeNum; i++)
        s = s+"\n\nTree [ "+std::to_string(i)+" ]\n"+this->treePool[i]->toString();
    s += "\n\n";
    return s;
};

std::string Forest::toStringTree(int tree_id){
    return this->treePool[tree_id]->toString();
};
/*
std::string Forest::toStringBests(){
    std::string s = "";
    for(int i=0; i<this->threshold; i++)
        s = s+"\n\nTree [ "+std::to_string(i)+" ]\n"+this->bestTrees[i].first->toString();
    s += "\n\n";
    return s;
};*/