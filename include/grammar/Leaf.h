#ifndef _INCLUDE_GRAMMAR_LEAF_H
#define _INCLUDE_GRAMMAR_LEAF_H

#include "include/grammar/INode.h"

class Leaf : public INode{
    private:
    INode* child;
    int randseed;
    double randmax;

    public:
    Leaf(double randmax);
    ~Leaf();
    double evaluate();
    void expand(int p_id, int depth);
};

#endif