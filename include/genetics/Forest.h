#ifndef _INCLUDE_GRAMMAR_FOREST_H
#define _INCLUDE_GRAMMAR_FOREST_H

#include<string>
#include<utility>

#include "include/genetics/Tree.h"

class Forest{
    private:
    Tree** treePool;
    //std::pair<int, double>* bestTrees;
    int treeNum, threshold, depthmax;
    double fitness(Tree* f, double* x_vals, double* y_vals, int pointsNum);

    public:
    Forest(int treeNum, int depthmax, int threshold, int randmax, int randseed);
    ~Forest();
    int* selectBests(double* x_vals, double* y_vals, int pointsNum);
    void crossover(int tree1_id, int tree2_id);
    void mutation(int tree_id);
    void newGeneration(int* bestTrees);
    std::string toString();
    std::string toStringTree(int tree_id);
    //std::string toStringBests();
};

#endif