#ifndef _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H
#define _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H

#include<string>
#include<utility>

#include "include/genetics/Tree.h"

class ParallelForest{
    private:
    Tree** treePool;
    //std::pair<int, double>* bestTrees;
    int treeNum, threshold, depthmax;

    public:
    double fitness(Tree* f, double* x_vals, double* y_vals, int pointsNum);
    ParallelForest(int treeNum, int depthmax, int threshold, int randmax, int randseed);
    ~ParallelForest();
    int* selectBests(double* x_vals, double* y_vals, int pointsNum);
    void crossover(int tree1_id, int tree2_id);
    void mutation(int tree_id);
    void newGeneration(int* bestTrees);
    Tree* getBest(double* x_vals, double* y_vals, int pointsNum);
    std::string toString();
    std::string toStringTree(int tree_id);
    //std::string toStringBests();
};

#endif