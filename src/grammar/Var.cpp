#include "include/grammar/Var.h"

double Var::evaluate(){
    return this->x;
};

INode* Var::expand(int p_id){
    return this;
};

void Var::setValue(double x_val){
    this->x = x_val;
};