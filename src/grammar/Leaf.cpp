#include "include/grammar/Leaf.h"

#include<cstdlib>
#include<ctime>

#include "include/grammar/Const.h"
#include "include/grammar/Var.h"

Leaf::Leaf(double randmax, int randseed){
    this->child = nullptr;
    this->randmax = randmax;
    std::srand(randseed); 
};

Leaf::~Leaf(){
    if(this->child != nullptr)
        delete this->child;
}

double Leaf::evaluate(){
    return this->child->evaluate();
};

void Leaf::expand(int depth){
    if(depth < 0)
        return;
    int p_id = 1 + (std::rand() % _LEAF_PROD_NUM);
    double c = 0.0;
    if(p_id == 1){
        while(c == 0.0){
            c = (double)std::rand();
            c = (c/(double)RAND_MAX)*this->randmax;
        }
    }
    this->expandLast(p_id, c);
};

void Leaf::expandLast(int p_id, double c){
    if(p_id < 1 || p_id >_LEAF_PROD_NUM)
        return;
    if(this->child != nullptr)
        delete this->child;
    
    switch(p_id){
        case 1:
        {
            this->child = new Const(c);
            break;
        }
        case 2:
        {
            this->child = new Var();
            break;
        }
        default : break;
    }
};

std::string Leaf::toString(){
    return this->child->toString();
};