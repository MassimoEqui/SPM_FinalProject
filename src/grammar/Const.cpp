#include "include/grammar/Const.h"

Const::Const(int val){
    this->val = val;
};

Const::~Const(){};

double Const::evaluate(double x_val){ return (double)this->val; };

void Const::expandRandom(int depth){};

INode** Const::getChildren(){ return nullptr; };

int Const::getChildrenNum(){ return 0; };

INode* Const::setChild(int child_id, INode* child){ return nullptr; };

INode* Const::copyToEnd(){ return new Const(this->val); };

std::string Const::toString(){ return std::to_string(this->val); };