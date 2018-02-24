#include "include/grammar/Var.h"

double Var::evaluate(){
    return this->x;
};

void Var::expand(int depth){};
void Var::expand(int p_id, int depth){};

void Var::setValue(double x_val){
    this->x = x_val;
};

std::string Var::toString(){
    return std::to_string(this->evaluate());
};