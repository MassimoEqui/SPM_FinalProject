#ifndef _INCLUDE_GRAMMAR_LEAF_H
#define _INCLUDE_GRAMMAR_LEAF_H

#define _LEAF_PROD_NUM 2

#include "include/grammar/INode.h"

class Leaf : public INode{
    private:
    INode* child;
    double randmax;

    public:
    Leaf(double randmax, int randseed);
    ~Leaf();
    double evaluate();
    void expand(int depth);
	std::string toString();

	void expandLast(int p_id, double c);
};

#endif