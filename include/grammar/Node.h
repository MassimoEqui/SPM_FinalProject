#ifndef _INCLUDE_GRAMMAR_NODE_H
#define _INCLUDE_GRAMMAR_NODE_H

#define CHILDREN_NUM 2
#define _NODE_PROD_NUM 3
#define _UNOP_PROD_NUM 4
#define EXP 1
#define SIN 2
#define COS 3
#define LOG 4
#define _BINOP_PROD_NUM 5
#define MIN 1
#define PLUS 2
#define TIMES 3
#define DIV 4
#define POW 5

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
	void expand(int p_id, int depth);
	std::string toString();
};

#endif