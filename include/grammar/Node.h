#ifndef _INCLUDE_GRAMMAR_NODE_H
#define _INCLUDE_GRAMMAR_NODE_H

#define CHILDREN_NUM 2
#define _NODE_PROD_NUM 3
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
	int randmax, p_id, unop, binop;
	INode* children[CHILDREN_NUM];

	public:
	Node(double randmax, int randseed);
	~Node();
	double evaluate();
	void expand(int depth);
	std::string toString();
	
	void expand(int p_id, int depth);
	INode** expandByOne(int p_id, int op);
};

#endif