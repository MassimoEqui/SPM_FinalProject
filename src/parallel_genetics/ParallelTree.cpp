#include "include/parallel_genetics/ParallelTree.h"

#include<cstdlib>
//DEBUG
#include<iostream>

ParallelTree::ParallelTree(int depth, int randmax, int randseed){
    std::srand(randseed);
    this->depth = depth;
    this->randmax = randmax;
    this->root = nullptr;
    if(depth >= 0){
        this->root = new Node(randmax, std::rand());
        this->root->expandRandom(depth);
    }
};

ParallelTree::~ParallelTree(){ delete this->root; };

double ParallelTree::evaluate(double x_val){
    if(this->root != nullptr)
        return this->root->evaluate(x_val);
    else 
        return -1.0;
};

void ParallelTree::mutation(int depth){
    this->getRandomSubtree(depth)->expandRandom(this->depth-depth);
};

INode* ParallelTree::getRandomSubtree(int depth){
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

int ParallelTree::getDepth(){ return this->depth; };

void ParallelTree::setDepth(int depth){ this->depth = depth; }

INode* ParallelTree::getRoot(){ return this->root; }

INode* ParallelTree::setRoot(Node* root){
    INode* oldRoot = this->root;
    this->root = root;
    return oldRoot;
}

ParallelTree* ParallelTree::copy(){
    ParallelTree* newTree = new ParallelTree(-1, this->randmax, std::rand());
    newTree->setDepth(this->depth);
    newTree->setRoot((Node*)this->root->copyToEnd());
    return newTree;
}

std::string ParallelTree::toString(){
    if(this->root != nullptr)
        return this->root->toString();
    else
        return "";
};