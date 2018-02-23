#ifndef _INCLUDE_GRAMMAR_NODE_H
#define _INCLUDE_GRAMMAR_NODE_H

#define CHILDREN_NUM 2
#define _NODE_PROD_NUM 3

#include "include/grammar/INode.h"

class Node : public INode{
	private:
	int randmax, p_id;
	INode* children[CHILDREN_NUM];

	public:
	Node(double randmax, int randseed);
	~Node();
	double evaluate();
	void expand(int depth);
};

#endif