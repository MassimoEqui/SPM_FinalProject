#include "include/genetics/Tree.h"

#include<cstdlib>
//DEBUG
#include<iostream>

Tree::Tree(int depth, int randmax, int randseed){
    std::srand(randseed);
    this->depth = depth;
    this->root = new Node(randmax, std::rand());
    this->root->expandRandom(depth);
};

Tree::~Tree(){ delete this->root; };

double Tree::evaluate(double x_val){
    if(this->root != nullptr)
        return this->root->evaluate(x_val);
    else 
        return -1.0;
};

void Tree::mutation(int depth){
    this->getRandomSubtree(depth)->expandRandom(this->depth-depth);
};

INode* Tree::getRandomSubtree(int depth){
    if(depth > this->depth)
        return nullptr;
    INode* subtree_root = this->root;
    INode** children = this->root->getChildren();
    int children_num = this->root->getChildrenNum();
    int branch = 0;
    for(int i=0; i<depth; i++){
        branch = std::rand() % children_num;
        subtree_root = children[branch];
        delete children;
        children = subtree_root->getChildren();
        children_num = subtree_root->getChildrenNum();  
    }
    delete children;
    return subtree_root;
};

std::string Tree::toString(){
    if(this->root != nullptr)
        return this->root->toString();
    else
        return "";
};