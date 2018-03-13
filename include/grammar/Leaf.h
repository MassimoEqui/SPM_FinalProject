#ifndef _INCLUDE_GRAMMAR_LEAF_H
#define _INCLUDE_GRAMMAR_LEAF_H

#define _LEAF_PROD_NUM 2
#define _LEAF_FIRST_PROD 1
#define _LEAF_SECOND_PROD 2

#include "include/grammar/INode.h"

class Leaf : public INode{
    private:
    INode* child;
    int randmax;

    public:
    Leaf(int randmax);
    ~Leaf();
    double evaluate(double x_val);
    void expandRandom(int depth);
    INode** getChildren();
    int getChildrenNum();
	INode* setChild(int child_id, INode* child);
	INode* copyToEnd();
	std::string toString();

	void expandLast(int p_id, int c);
};

#endif