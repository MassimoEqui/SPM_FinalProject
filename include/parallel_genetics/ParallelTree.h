#ifndef _INCLUDE_PARALLELGENETICS_PARALLELTREE_H
#define _INCLUDE_PARALLELGENETICS_PARALLELTREE_H

#include<string>

#include "include/grammar/grammar.h"

class ParallelTree{
    private:
    Node* root;
    int depth, randmax;

    public:
    ParallelTree(int depth, int randmax, int randseed);
    ~ParallelTree();
    double evaluate(double x_val);
    void mutation(int depth);
    INode* getRandomSubtree(int depth);
    int getDepth();
    void setDepth(int depth);
    INode* getRoot();
    INode* setRoot(Node* root);
    ParallelTree* copy();
    std::string toString();
};

#endif