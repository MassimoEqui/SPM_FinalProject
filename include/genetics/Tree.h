#ifndef _INCLUDE_GRAMMAR_TREE_H
#define _INCLUDE_GRAMMAR_TREE_H

#include<string>

#include "include/grammar/grammar.h"

class Tree{
    private:
    Node* root;
    int depth;

    public:
    Tree(int depth, int randmax, int randseed);
    ~Tree();
    double evaluate(double x_val);
    void mutation(int depth);
    INode* getRandomSubtree(int depth);
    int getDepth();
    INode* getRoot();
    INode* setRoot(Node* root);
    std::string toString();
};

#endif