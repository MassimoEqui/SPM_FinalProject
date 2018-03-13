#ifndef _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H
#define _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H

#include<string>
#include<utility>
#include<vector>

#include "include/genetics/Forest.h"
class ParallelForest: public Forest{
    private:
    int nw_farm, nw_parallelFor;

    protected:
    virtual void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    ParallelForest(int treeNum, int depthmax, int randmax, int nw_F, int nw_PF);
    ~ParallelForest();

    virtual double fitness(Tree* f, double* x_vals, double* y_vals, int points_no);
};

#endif