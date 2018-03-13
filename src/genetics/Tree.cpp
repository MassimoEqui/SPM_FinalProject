#include "include/genetics/Tree.h"

#include<cstdlib>
//DEBUG
#include<iostream>

Tree::Tree(int depth, int randmax){
    this->depth = depth;
    this->randmax = randmax;
    this->root = nullptr;
    if(depth >= 0){
        this->root = new Node(randmax);
        this->root->expandRandom(depth);
    }
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

int Tree::getDepth(){ return this->depth; };

void Tree::setDepth(int depth){ this->depth = depth; }

INode* Tree::getRoot(){ return this->root; }

INode* Tree::setRoot(Node* root){
    INode* oldRoot = this->root;
    this->root = root;
    return oldRoot;
}

Tree* Tree::copy(){
    Tree* newTree = new Tree(-1, this->randmax);
    newTree->setDepth(this->depth);
    newTree->setRoot((Node*)this->root->copyToEnd());
    return newTree;
}

std::string Tree::toString(){
    if(this->root != nullptr)
        return this->root->toString();
    else
        return "";
};