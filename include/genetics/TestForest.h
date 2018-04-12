#ifndef _INCLUDE_GENETICS_TESTFOREST_H
#define _INCLUDE_GENETICS_TESTFOREST_H

#include<chrono>

#include "include/genetics/Forest.h"

class TestForest: public Forest{
    private:
    int nw;

    public:
    TestForest(int treeNum, int depthmax, int randmax, int nw);
    ~TestForest();
    void setFitnessUpdated();
    std::chrono::duration<double> updatePoolFitness(double* x_vals, double* y_vals, int points_no, int partition);

};

#endif