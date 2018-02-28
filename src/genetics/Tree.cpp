#include "include/genetics/Tree.h"

#include<cstdlib>

Tree::Tree(int depth, int randmax, int randseed){
    std::srand(randseed);
    this->depth = depth;
    this->root = new Node(randmax, std::rand());
    this->root->expandRandom(depth);
};

Tree::~Tree(){ delete this->root; };

double Tree::evaluate(double x_val){ return this->root->evaluate(x_val); };

void Tree::mutation(int depth){
    this->getRandomSubtree(depth)->expandRandom(this->depth-depth);
};

INode* Tree::getRandomSubtree(int depth){
    INode* subtree_root = this->root;
    INode** children = this->root->getChildren();
    int branch = 1;
    for(int i=0; i<depth; i++){
        if(subtree_root->getChildrenNum() > 1);
            branch = 1 + (std::rand() % CHILDREN_NUM);
        subtree_root = children[branch];
        children = subtree_root->getChildren();        
    }
    return subtree_root;
};