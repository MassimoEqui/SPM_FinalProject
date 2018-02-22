#include "include/grammar/Leaf.h"

#include<cstdlib>
#include<ctime>

#include "include/grammar/Const.h"
#include "include/grammar/Var.h"

Leaf::Leaf(double randmax){
    this->randmax = randmax;
    this->randseed = std::time(nullptr);
};

double Leaf::evaluate(){
    return this->child->evaluate();
};

void Leaf::expand(int p_id, int depth){
    delete this->child;
    switch(p_id){
        case 1:
        {
            std::srand(this->randseed);
            double c = (double)std::rand();
            c = c/(double)RAND_MAX*this->randmax;
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