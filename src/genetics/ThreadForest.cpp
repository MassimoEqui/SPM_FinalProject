#include "include/genetics/ThreadForest.h"

#include<cstdlib>
#include<cmath>
#include<vector>
#include<functional>

ThreadForest::ThreadForest(int treeNum, int depthmax, int randmax, int nw)
    :Forest(treeNum, depthmax, randmax){
    this->nw = nw;
};

ThreadForest::~ThreadForest(){};

void ThreadForest::updatePoolFitness(double* x_vals, double* y_vals, int points_no){
    if(this->fitnessUpdated) return;
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    int delta = this->treeNum/this->nw;
    std::vector<std::thread> pool;
    for(int i=0; i<this->nw-1; i++)
        pool.push_back(std::thread(ThreadForest::worker,this,i*delta,(i+1)*delta,x_vals,y_vals,points_no));
    pool.push_back(std::thread(ThreadForest::worker,this,(this->nw-1)*delta, this->treeNum,x_vals,y_vals,points_no));
    
    for(int i=0; i<this->nw; i++)
        pool[i].join();

    end = std::chrono::system_clock::now();
    this->fitnessUpdate_time += end - start;
    this->fitnessUpdated = true;
};

void ThreadForest::worker(ThreadForest* forest, int i_start, int i_stop, double* x_vals, double* y_vals, int points_no){
    for(int i=i_start; i<i_stop; i++)
        forest->treePool[i].second =
            forest->fitness(forest->treePool[i].first, x_vals, y_vals, points_no);
};