#ifndef _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H
#define _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H

#include<string>
#include<utility>
#include<vector>

#include "include/parallel_genetics/ParallelTree.h"

class ParallelForest{
    private:
    std::pair<ParallelTree*, double>* treePool;
    int treeNum, threshold, depthmax;

    public:
    double fitness(ParallelTree* f, double* x_vals, double* y_vals, int pointsNum);
    ParallelForest(int treeNum, int depthmax, int threshold, int randmax, int randseed);
    ~ParallelForest();
    int* selectBests(double* x_vals, double* y_vals, int pointsNum);
    ParallelTree* crossover(int tree1_id, int tree2_id);
    ParallelTree* mutation(int tree_id);
    void newGeneration(std::vector<ParallelTree*>& bestTrees);
    ParallelTree* getBest(double* x_vals, double* y_vals, int pointsNum);
    ParallelTree* getTree(int tree_id);
    std::string toString();
    std::string toStringTree(int tree_id);
    //std::string toStringBests();
};

#endif