#include "include/grammar/Const.h"

Const::Const(int val){
    this->val = val;
};

Const::~Const(){};
double Const::evaluate(double x_val){ return this->val; }; 

void Const::expandRandom(int depth){};

INode** Const::getChildren(){ return nullptr; };

int Const::getChildrenNum(){ return 0; };

INode* Const::setChild(int child_id, INode* child){ return nullptr; };

INode* Const::copyToEnd(){ return new Const(this->val); };


//cast needed for compatibility with the icc compiler
std::string Const::toString(){ return std::to_string((long double)this->val); };