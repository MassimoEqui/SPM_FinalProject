#include "include/grammar/Node.h"

#include<cstdlib>
#include<ctime>
#include<cmath>
#include<limits>
//DEBUG
#include<iostream>
#include "include/grammar/Leaf.h"

Node::Node(double randmax, int randseed){
	std::srand(randseed);
	this->randmax = randmax;
	this->p_id = -1;
	this->unop = -1;
	this->binop = -1;
	for(int i=0; i<CHILDREN_NUM; i++)
		this->children[i] = nullptr; 
};

Node::~Node(){
	for(int i=0; i<CHILDREN_NUM; i++)
		if(children[i] != nullptr)
			delete children[i];
}

double Node::evaluate(double x_val){
	switch(this->p_id){
		case 1: return this->children[0]->evaluate(x_val);
		case 2: {
			switch(this->unop){
				case EXP :{
					return std::exp(this->children[0]->evaluate(x_val));
				}
				case SIN :{
					return std::sin(this->children[0]->evaluate(x_val));
				}
				case COS :{
					return std::cos(this->children[0]->evaluate(x_val));
				}
				case LOG :{
					return std::log(this->children[0]->evaluate(x_val));
				}
				default : return 2.0;
			}			
		}
		case 3: {
			switch(this->binop){
				case MIN :{
					return
						this->children[0]->evaluate(x_val) -
						this->children[1]->evaluate(x_val);
				}
				case PLUS :{
					return
						this->children[0]->evaluate(x_val) +
						this->children[1]->evaluate(x_val);
				}
				case TIMES :{
					return
						this->children[0]->evaluate(x_val) *
						this->children[1]->evaluate(x_val);
				}
				case DIV :{
					return
						this->children[0]->evaluate(x_val) /
						this->children[1]->evaluate(x_val);
				}
				case POW :{
					return std::pow(
						this->children[0]->evaluate(x_val),
						this->children[1]->evaluate(x_val));
				}
				default : return std::numeric_limits<double>::quiet_NaN();
			}
		}
		default : return 0.0;
	}
};

void Node::expand(int depth){
	int children_depth = depth-1;	
	if(depth < 0)
		return;
	if(depth == 0){
		this->p_id = 1;
		children_depth = 0;
	}
	else
		this->p_id = 2 + (std::rand() % (_NODE_PROD_NUM-1));
	
	int op;
	switch(this->p_id){
		case 1:{ op = -1; break; }
		case 2:{ op = EXP + (std::rand() % _UNOP_PROD_NUM);	break; }
		case 3:{ op = MIN + (std::rand() % _BINOP_PROD_NUM); break; }
		default:{ op = -1; break; }
	}

	INode** chldr = this->expandByOne(this->p_id,op);
	
	for(int i=0; i<CHILDREN_NUM; i++){
		if(this->children[i] != nullptr){
			this->children[i] = chldr[i];
			this->children[i]->expand(children_depth);
		}		
	}
};

INode** Node::expandByOne(int p_id, int op){
	if(p_id<1 || p_id>_NODE_PROD_NUM)
		return nullptr;

	for(int i=0; i<CHILDREN_NUM; i++)
		if(children[i] != nullptr){
			delete children[i];
			children[i] = nullptr;
		}
	
	this->p_id = p_id;
	this->unop = -1;
	this->binop = -1;

	switch(p_id){
		case 1: {//<leaf>
			this->children[0] = new Leaf(this->randmax, std::rand());
			break;
		}
		case 2: {//<unop> <node>
			this->unop = op;
			this->children[0] = new Node(this->randmax, std::rand());
			break;
		}
		case 3: {//<node> <binop> <node>
			this->binop = op;
			this->children[0] = new Node(this->randmax, std::rand());
			this->children[1] = new Node(this->randmax, std::rand());
			break;
		}
		default: break;
	}

	INode** chldr = new INode*[CHILDREN_NUM];
	for(int i=0; i<CHILDREN_NUM; i++)
		chldr[i] = this->children[i];
	return chldr;
};

std::string Node::toString(){
	std::string s = "";  
	switch(this->p_id){
		case 1: {
			s = this->children[0]->toString();
			break;
		}
		case 2: {
			switch(this->unop){
				case EXP :{
					s = "exp";
					break;
				}
				case SIN :{
					s = "sin";
					break;
				}
				case COS :{
					s = "cos";
					break;
				}
				case LOG :{
					s = "log";
					break;
				}
				default : break;
			}
			if(!s.empty())
				s = s + "("+this->children[0]->toString()+")";
			break;			
		}
		case 3: {
			switch(this->binop){
				case MIN :{
					s = "-";
					break;
				}
				case PLUS :{
					s = "+";
					break;
				}
				case TIMES :{
					s = "*";
					break;
				}
				case DIV :{
					s = "/";
					break;
				}
				case POW :{
					s = "^";
					break;
				}
				default : return nullptr;
			}

			if(!s.empty())
				s = "[ "+this->children[0]->toString()+
					s+
					this->children[1]->toString()+" ]";

			break;
		}
		default : break;
	}

	return s;
};