#ifndef _INCLUDE_GRAMMAR_INODE_H
#define _INCLUDE_GRAMMAR_INODE_H

class INode {
public:
	virtual double evaluate() = 0;
	virtual INode* expand(int p_id) = 0;
};

#endif