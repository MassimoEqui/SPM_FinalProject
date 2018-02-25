#include "include/grammar/Var.h"

Var::Var(){
    this->x = 0.0;
};

Var::~Var(){};

double Var::evaluate(){
    return this->x;
};

void Var::expand(int depth){};

void Var::setValue(double x_val){
    this->x = x_val;
};

std::string Var::toString(){
    return "x";
};