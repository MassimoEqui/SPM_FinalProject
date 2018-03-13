#ifndef _INCLUDE_PARALLELGENETICS_FOREST_H
#define _INCLUDE_PARALLELGENETICS_FOREST_H

#include<string>
#include<utility>
#include<vector>

#include "include/genetics/Tree.h"

class Forest{
    protected:
    std::pair<Tree*, double>* treePool;
    std::pair<Tree*, double> bestTree;
    long treeNum;
    int depthmax, nw_F, nw_PF;
    bool fitnessUpdated, bestTreeUpdated;
    void updateBestTree(double* x_vals, double* y_vals, int points_no);

    virtual void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    Forest(long treeNum, int depthmax, int randmax);
    ~Forest();
    int* selectBests(double* x_vals, double* y_vals, int points_no, int threshold);
    Tree* crossover(int tree1_id, int tree2_id);
    Tree* mutation(int tree_id);
    void newGeneration(std::vector<Tree*>& bestTrees);
    std::pair<Tree*, double>* getTreePool();
    Tree* getBestTree(double* x_vals, double* y_vals, int pointsNum);
    double getBestFitness(double* x_vals, double* y_vals, int pointsNum);
    Tree* getTree(int tree_id);
    std::string toString();
    
    virtual double fitness(Tree* f, double* x_vals, double* y_vals, int points_no);
};

#endif