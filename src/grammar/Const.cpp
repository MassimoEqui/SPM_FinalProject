#include "include/grammar/Const.h"

Const::Const(double val){
    this->val = val;
};

double Const::evaluate(){
    return this->val;
};

void Const::expand(int p_id, int depth){};