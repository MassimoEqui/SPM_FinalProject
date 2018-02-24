#ifndef _INCLUDE_GRAMMAR_INODE_H
#define _INCLUDE_GRAMMAR_INODE_H

class INode {
public:
	virtual double evaluate() = 0;
	virtual void expand(int depth) = 0;
	virtual void expand(int p_id, int depth) = 0;
};

#endif