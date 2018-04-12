#include "include/genetics/TestForest.h"

#include<cstdlib>
#include<cmath>
#include<vector>
#include<functional>


TestForest::TestForest(int treeNum, int depthmax, int randmax, int nw)
    :Forest(treeNum, depthmax, randmax){
    this->nw = nw;
};

TestForest::~TestForest(){};

std::chrono::duration<double> TestForest::updatePoolFitness(double* x_vals, double* y_vals, int points_no, int worker_idx){    
    if(this->fitnessUpdated) return std::chrono::system_clock::duration::zero();

    int delta = this->treeNum/this->nw;
    int i_stop, i_start = delta*worker_idx;
    if(worker_idx < this->nw-1)
        i_stop = delta*(worker_idx+1);
    else
        i_stop = this->treeNum;

    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    for(int i=i_start; i<i_stop; i++)
        this->treePool[i].second =
            this->fitness(this->treePool[i].first, x_vals, y_vals, points_no);

    end = std::chrono::system_clock::now();
    this->fitnessUpdate_time += end - start;
    return end - start;
};

void TestForest::setFitnessUpdated(){
    this->fitnessUpdated = true;
}