#include "include/grammar/Leaf.h"

#include<cstdlib>
#include<ctime>
//DEBUG
#include<iostream>

#include "include/grammar/Const.h"
#include "include/grammar/Var.h"

Leaf::Leaf(int randmax){
    this->child = nullptr;
    this->randmax = randmax; 
};

Leaf::~Leaf(){
    if(this->child != nullptr){
        delete this->child;
    }
}

double Leaf::evaluate(double x_val){if(this->child != nullptr)
        return this->child->evaluate(x_val);
    else
        return -1.0;
};

void Leaf::expandRandom(int depth){
    if(depth < 0)
        return;
    int p_id = _LEAF_FIRST_PROD + (std::rand() % _LEAF_PROD_NUM);
    int c = 0.0;
    if(p_id == _LEAF_FIRST_PROD)
        c = std::rand()%this->randmax;
    this->expandLast(p_id, c);
};

void Leaf::expandLast(int p_id, int c){
    if(p_id < _LEAF_FIRST_PROD || p_id >_LEAF_PROD_NUM)
        return;
    if(this->child != nullptr)
        delete this->child;
    
    switch(p_id){
        case _LEAF_FIRST_PROD:
        {
            this->child = new Const(c);
            break;
        }
        case _LEAF_SECOND_PROD:
        {
            this->child = new Var();
            break;
        }
        default : break;
    }
};

INode** Leaf::getChildren(){
    INode** children = new INode*[CHILDREN_NUM];
    for(int i=0; i<CHILDREN_NUM; i++)
        children[i] = nullptr;
    children[0] = this->child;
    return children;
};

int Leaf::getChildrenNum(){ 
    if(this->child != nullptr)
        return 1;
    else
        return 0;
};

INode* Leaf::setChild(int child_id, INode* child){
    INode* oldChild = this->child;
    this->child = child;
    return oldChild;
};

INode* Leaf::copyToEnd(){
    INode* newLeaf = new Leaf(this->randmax);
    if(this->child != nullptr){
        INode* newChild = this->child->copyToEnd();
        newLeaf->setChild(0, newChild);
    }
    return newLeaf;
};

std::string Leaf::toString(){
    if(this->child != nullptr)
        return this->child->toString();
    else
        return "";
};