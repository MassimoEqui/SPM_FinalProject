#include "include/grammar/Var.h"

Var::Var(){};

Var::~Var(){};

double Var::evaluate(double x_val){
    return x_val;
};

void Var::expand(int depth){};

std::string Var::toString(){
    return "x";
};