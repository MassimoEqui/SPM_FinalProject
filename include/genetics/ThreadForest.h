#ifndef _INCLUDE_GENETICS_THREADFOREST_H
#define _INCLUDE_GENETICS_THREADFOREST_H

#include<vector>
#include<thread>

#include "include/genetics/Forest.h"

class ThreadForest : public Forest{
    private:
    int nw;
    static void worker(ThreadForest* forest, int i_start, int i_stop, double* x_vals, double* y_vals, int points_no);

    protected:
    virtual void updatePoolFitness(double* x_vals, double* y_vals, int points_no);

    public:
    ThreadForest(int treeNum, int depthmax, int randmax, int nw);
    ~ThreadForest();
};

#endif