#ifndef _INCLUDE_GENETICS_TREE_H
#define _INCLUDE_GENETICS_TREE_H

#include<string>

#include "include/grammar/grammar.h"

class Tree{
    private:
    Node* root;
    int depth, randmax;

    public:
    Tree(int depth, int randmax);
    ~Tree();
    double evaluate(double x_val);
    void mutation(int depth);
    INode* getRandomSubtree(int depth);
    int getDepth();
    void setDepth(int depth);
    INode* getRoot();
    INode* setRoot(Node* root);
    Tree* copy();
    std::string toString();
};

#endif