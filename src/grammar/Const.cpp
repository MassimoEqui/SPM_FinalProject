#include "include/grammar/Const.h"

Const::Const(double val){
    this->val = val;
};

Const::~Const(){};

double Const::evaluate(double x_val){
    return this->val;
};

void Const::expand(int depth){};

std::string Const::toString(){
    return std::to_string(this->val);
};