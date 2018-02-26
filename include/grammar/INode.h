#ifndef _INCLUDE_GRAMMAR_INODE_H
#define _INCLUDE_GRAMMAR_INODE_H

#include<string>

class INode {
public:
	~INode(){};
	virtual double evaluate() = 0;
	virtual void expand(int depth) = 0;
	virtual std::string toString() = 0;
};

#endif