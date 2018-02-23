#ifndef _INCLUDE_GRAMMAR_CONST
#define _INCLUDE_GRAMMAR_CONST

#include "include/grammar/INode.h"

class Const : public INode {
private:
    double val;

public:
	Const(double val);
	~Const();
	double evaluate();
	void expand(int depth);
};

#endif