#include "include/genetics/ParallelForest.h"

#include<cstdlib>
#include<cmath>
#include<vector>
#include<functional>

using namespace ff;
//DEBUG
#include<iostream>
#include<iomanip>

ParallelForest::ParallelForest(int treeNum, int depthmax, int randmax, int nw)
    :Forest(treeNum, depthmax, randmax){
    this->nw = nw;
    this->pf = std::make_unique<ParallelFor>(nw);
};

ParallelForest::~ParallelForest(){};

void ParallelForest::updatePoolFitness(double* x_vals, double* y_vals, int points_no){
    if(this->fitnessUpdated) return;
    this->pf->parallel_for(0, this->treeNum, 1, 0, [&](const long i){
        treePool[i].second =
            this->fitness(treePool[i].first, x_vals, y_vals, points_no);
    },this->nw);
    this->fitnessUpdated = true;
};