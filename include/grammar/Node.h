#ifndef _INCLUDE_GRAMMAR_NODE_H
#define _INCLUDE_GRAMMAR_NODE_H 

#include "include/grammar/INode.h"

class Node : public INode{
	public:
	Node(){};
	~Node(){};
	double evaluate();
	void expand(int p_id, int depth);
};

#endif