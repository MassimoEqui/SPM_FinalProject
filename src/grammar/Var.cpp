#include "include/grammar/Var.h"

Var::Var(){};

Var::~Var(){};

double Var::evaluate(double x_val){ return x_val; };

void Var::expandRandom(int depth){};

INode** Var::getChildren(){ return nullptr; };

int Var::getChildrenNum(){ return 0; };

INode* Var::setChild(int child_id, INode* child){ return nullptr; };

INode* Var::copyToEnd(){ return new Var(); };

std::string Var::toString(){ return "x"; };