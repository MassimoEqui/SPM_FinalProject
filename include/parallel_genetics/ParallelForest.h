#ifndef _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H
#define _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H

#include<string>
#include<utility>
#include<vector>

#include "include/parallel_genetics/ParallelTree.h"

class ParallelForest{
    private:
    std::pair<ParallelTree*, double>* treePool;
    std::pair<ParallelTree*, double> bestTree;
    int treeNum, depthmax, nw_farm, nw_parallelFor;
    bool fitnessUpdated, bestTreeUpdated;
    void updateBestTree(double* x_vals, double* y_vals, int points_no);
    void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    ParallelForest(int treeNum, int depthmax, int randmax, int randseed, int nw_farm, int nw_parallelFor);
    ~ParallelForest();
    double fitness(ParallelTree* f, double* x_vals, double* y_vals, int points_no);
    int* selectBests(double* x_vals, double* y_vals, int points_no, int threshold);
    ParallelTree* crossover(int tree1_id, int tree2_id);
    ParallelTree* mutation(int tree_id);
    void newGeneration(std::vector<ParallelTree*>& bestTrees);
    std::pair<ParallelTree*, double>* getTreePool();
    //ParallelTree* getBest(double* x_vals, double* y_vals, int points_no);
    ParallelTree* getBestTree(double* x_vals, double* y_vals, int pointsNum);
    double getBestFitness(double* x_vals, double* y_vals, int pointsNum);
    ParallelTree* getTree(int tree_id);
    std::string toString();
    //std::string toStringTree(int tree_id);
    //std::string toStringBests();
};

#endif