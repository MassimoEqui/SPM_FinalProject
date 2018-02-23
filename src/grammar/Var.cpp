#include "include/grammar/Var.h"

double Var::evaluate(){
    return this->x;
};

void Var::expand(int depth){};

void Var::setValue(double x_val){
    this->x = x_val;
};