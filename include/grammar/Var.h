#ifndef _INCLUDE_GRAMMAR_VAR_H
#define _INCLUDE_GRAMMAR_VAR_H

#include <iostream>

#include "include/grammar/INode.h"

class Var : public INode {
private:
    double x;

public:
	Var(){ this->x = 0.0; }
	~Var(){}
	double evaluate();
	INode* expand(int p_id);

	void setValue(double x_val);
};

#endif