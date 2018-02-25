#include "include/grammar/Node.h"

#include<cstdlib>
#include<ctime>
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

double Node::evaluate(){
	switch(this->p_id){
		case 1: return this->children[0]->evaluate();
		case 2: {
			switch(this->unop){
				case EXP :{
					//TODO
					return 0.1;
				}
				case SIN :{
					//TODO
					return 0.2;
				}
				case COS :{
					//TODO
					return 0.3;
				}
				case LOG :{
					//TODO
					return 0.4;
				}
				default : return 2.0;
			}			
		}
		case 3: {
			switch(this->binop){
				case MIN :{
					//TODO
					return 0.1;
				}
				case PLUS :{
					//TODO
					return 0.2;
				}
				case TIMES :{
					//TODO
					return 0.3;
				}
				case DIV :{
					//TODO
					return 0.4;
				}
				case POW :{
					//TODO
					return 0.5;
				}
				default : return 3.0;
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
	
	//this->expand(this->p_id, depth);
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
/*
void Node::expand(int p_id, int depth){
	if(depth < 0)
		return;
	if(p_id<1 || p_id>_NODE_PROD_NUM)
		return;

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
			children[0] = new Leaf(this->randmax, std::rand());
			children[0]->expand(0);
			break;
		}
		case 2: {//<unop> <node>
			this->unop = EXP + (std::rand() % _UNOP_PROD_NUM);
			this->children[0] = new Node(this->randmax, std::rand());
			this->children[0]->expand(depth-1);
			break;
		}
		case 3: {//<node> <binop> <node>
			this->binop = MIN + (std::rand() % _BINOP_PROD_NUM);
			this->children[0] = new Node(this->randmax, std::rand());
			this->children[1] = new Node(this->randmax, std::rand());
			this->children[0]->expand(depth-1);
			this->children[1]->expand(depth-1);
			break;
		}
		default: break;
	}
};
*/
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
					s = "logs";
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
				s = "["+this->children[0]->toString()+
					s+
					this->children[1]->toString()+"]";

			break;
		}
		default : break;
	}

	return s;
};