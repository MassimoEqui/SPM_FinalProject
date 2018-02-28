#ifndef _INCLUDE_GRAMMAR_NODE_H
#define _INCLUDE_GRAMMAR_NODE_H

#define _NODE_PROD_NUM 3
#define _NODE_FIRST_PROD 1
#define _NODE_SECOND_PROD 2
#define _NODE_THIRD_PROD 3

#define _UNOP_PROD_NUM 4
#define UNOP 1
#define EXP 11
#define SIN 12
#define COS 13
#define LOG 14

#define _BINOP_PROD_NUM 5
#define BINOP 2
#define MIN 21
#define PLUS 22
#define TIMES 23
#define DIV 24
#define POW 25

#include "include/grammar/INode.h"

class Node : public INode{
	private:
	int randmax, p_id, unop, binop, children_num;
	INode* children[CHILDREN_NUM];
	void setParameters(int p_id, int unop, int binop, int children_num);

	public:
	Node(double randmax, int randseed);
	~Node();
	double evaluate(double x_val);
	void expandRandom(int depth);
	INode** getChildren();
	int getChildrenNum();
	INode* setChild(int child_id, INode* child);
	INode* copyToEnd();
	std::string toString();
	
	INode** expandByOne(int p_id, int op);
};

#endif