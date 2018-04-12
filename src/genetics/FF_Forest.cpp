#include "include/genetics/FF_Forest.h"

#include<cstdlib>
#include<cmath>
#include<vector>
#include<functional>

using namespace ff;

FF_Forest::FF_Forest(int treeNum, int depthmax, int randmax, int nw)
    :Forest(treeNum, depthmax, randmax){
    this->nw = nw;
    this->pf = std::unique_ptr<ff::ParallelFor>(new ParallelFor(nw));
};

FF_Forest::~FF_Forest(){};

void FF_Forest::updatePoolFitness(double* x_vals, double* y_vals, int points_no){    
    if(this->fitnessUpdated) return;

    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    this->pf->parallel_for(0, this->treeNum, 1, 0, [&](const long i){
        treePool[i].second =
            this->fitness(treePool[i].first, x_vals, y_vals, points_no);
    },this->nw);

    end = std::chrono::system_clock::now();
    this->fitnessUpdate_time += end - start;
    this->fitnessUpdated = true;
};