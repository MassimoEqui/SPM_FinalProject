#ifndef _INCLUDE_GRAMMAR_VAR_H
#define _INCLUDE_GRAMMAR_VAR_H

#include <iostream>

#include "include/grammar/INode.h"

class Var : public INode {
private:
    double x;

public:
	Var();
	~Var();
	//From INode
	double evaluate();
	void expand(int depth);
	std::string toString();

	void setValue(double x_val);
};

#endif