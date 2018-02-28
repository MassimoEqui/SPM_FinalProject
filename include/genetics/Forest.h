#ifndef _INCLUDE_GRAMMAR_FOREST_H
#define _INCLUDE_GRAMMAR_FOREST_H

#include "include/genetics/Tree.h"

class Forest{
    private:
    Tree** treePool;
    int treeNum, threshold;

    public:
    Forest(int treeNum, int depth, int threshold, int randmax, int randseed);
    ~Forest();
    void crossover(int depth, int tree1_id, int tree2_id);
    void mutation(int depth, int tree_id);
};

#endif