#ifndef _INCLUDE_GENETICS_FF_FOREST_H
#define _INCLUDE_GENETICS_FF_FOREST_H

#include<string>
#include<utility>
#include<vector>
#include<memory>

#include <ff/parallel_for.hpp>
#include "include/genetics/Forest.h"

class FF_Forest: public Forest{
    private:
    int nw;
    std::unique_ptr<ff::ParallelFor> pf;

    protected:
    virtual void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    FF_Forest(int treeNum, int depthmax, int randmax, int nw);
    ~FF_Forest();

};

#endif