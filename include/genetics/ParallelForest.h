#ifndef _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H
#define _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H

#include<string>
#include<utility>
#include<vector>

#include "include/genetics/Forest.h"
//#include "include/genetics/Tree.h"
/*
class ParallelForest{
    private:
    std::pair<Tree*, double>* treePool;
    std::pair<Tree*, double> bestTree;
    int treeNum, depthmax, nw_farm, nw_parallelFor;
    bool fitnessUpdated, bestTreeUpdated;
    void updateBestTree(double* x_vals, double* y_vals, int points_no);
    void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    ParallelForest(int treeNum, int depthmax, int randmax, int randseed, int nw_farm, int nw_parallelFor);
    ~ParallelForest();
    double fitness(Tree* f, double* x_vals, double* y_vals, int points_no);
    int* selectBests(double* x_vals, double* y_vals, int points_no, int threshold);
    Tree* crossover(int tree1_id, int tree2_id);
    Tree* mutation(int tree_id);
    void newGeneration(std::vector<Tree*>& bestTrees);
    std::pair<Tree*, double>* getTreePool();
    //Tree* getBest(double* x_vals, double* y_vals, int points_no);
    Tree* getBestTree(double* x_vals, double* y_vals, int pointsNum);
    double getBestFitness(double* x_vals, double* y_vals, int pointsNum);
    Tree* getTree(int tree_id);
    std::string toString();
    //std::string toStringTree(int tree_id);
    //std::string toStringBests();
};*/

class ParallelForest: public Forest{
    private:
    int nw_farm, nw_parallelFor;

    protected:
    virtual void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    ParallelForest(int treeNum, int depthmax, int randmax, int randseed, int nw_farm, int nw_parallelFor);
    ~ParallelForest();
    
    virtual double fitness(Tree* f, double* x_vals, double* y_vals, int points_no);
};

#endif