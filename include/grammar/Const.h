#ifndef _INCLUDE_GRAMMAR_CONST
#define _INCLUDE_GRAMMAR_CONST

#include "include/grammar/INode.h"

class Const : public INode {
private:
    int val;

public:
	Const(int val);
	~Const();
	double evaluate(double x_val);
	void expandRandom(int depth);
	INode** getChildren();
	int getChildrenNum();
	INode* setChild(int child_id, INode* child);
	INode* copyToEnd();
	std::string toString();
};

#endif