#ifndef _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H
#define _INCLUDE_PARALLELGENETICS_PARALLELFOREST_H

#include<string>
#include<utility>
#include<vector>
#include<memory>

#include <ff/parallel_for.hpp>
#include "include/genetics/Forest.h"
class ParallelForest: public Forest{
    private:
    int nw;
    std::unique_ptr<ff::ParallelFor> pf;

    protected:
    virtual void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    ParallelForest(int treeNum, int depthmax, int randmax, int nw);
    ~ParallelForest();

    //virtual double fitness(Tree* f, double* x_vals, double* y_vals, int points_no);
};

#endif