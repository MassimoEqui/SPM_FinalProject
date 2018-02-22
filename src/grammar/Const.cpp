#include "include/grammar/Const.h"

Const::Const(double val){
    this->val = val;
}

double Const::evaluate(){
    return this->val;
}

INode* Const::expand(int p_id){
    return this;
}