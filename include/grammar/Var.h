#ifndef _INCLUDE_GRAMMAR_VAR_H
#define _INCLUDE_GRAMMAR_VAR_H

#include <iostream>

#include "include/grammar/INode.h"

class Var : public INode {
public:
	Var();
	~Var();
	//From INode
	double evaluate(double x_val);
	void expandRandom(int depth);
	INode** getChildren();
	int getChildrenNum();
	INode* setChild(int child_id, INode* child);
	INode* copyToEnd();
	std::string toString();
};

#endif