#ifndef _INCLUDE_GENETICS_FOREST_H
#define _INCLUDE_GENETICS_FOREST_H

#include<string>
#include<utility>
#include<vector>
#include<chrono>

#include "include/genetics/Tree.h"

class Forest{
    protected:
    std::pair<Tree*, double>* treePool;
    std::pair<Tree*, double> bestTree;
    long treeNum;
    int depthmax;
    bool fitnessUpdated, bestTreeUpdated;
	std::chrono::duration<double> fitnessUpdate_time;

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
    std::chrono::duration<double> getFitnessUpdateTime();
    std::chrono::duration<double> resetFitnessUpdateTime();
    std::string toString();
    
    virtual double fitness(Tree* f, double* x_vals, double* y_vals, int points_no);
};

#endif