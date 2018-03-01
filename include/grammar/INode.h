#ifndef _INCLUDE_GRAMMAR_INODE_H
#define _INCLUDE_GRAMMAR_INODE_H

#include<string>

#define CHILDREN_NUM 2

class INode {
public:
	virtual ~INode(){};
	virtual double evaluate(double x_val) = 0;
	virtual void expandRandom(int depth) = 0;
	virtual INode** getChildren() = 0;
	virtual int getChildrenNum() = 0;
	virtual INode* setChild(int child_id, INode* child) = 0;
	virtual INode* copyToEnd() = 0;
	virtual std::string toString() = 0;
};

#endif