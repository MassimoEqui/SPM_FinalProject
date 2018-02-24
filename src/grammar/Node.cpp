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
	if(depth < 0)
		return;
	if(depth == 0)
		this->p_id = 1;
	else
		this->p_id = 2 + (std::rand() % (_NODE_PROD_NUM-1));
	
	this->expand(this->p_id, depth);
};


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
			this->unop = 1 + (std::rand() % _UNOP_PROD_NUM);
			this->children[0] = new Node(this->randmax, std::rand());
			this->children[0]->expand(depth-1);
			break;
		}
		case 3: {//<node> <binop> <node>
			this->binop = 1 + (std::rand() % _BINOP_PROD_NUM);
			this->children[0] = new Node(this->randmax, std::rand());
			this->children[1] = new Node(this->randmax, std::rand());
			this->children[0]->expand(depth-1);
			this->children[1]->expand(depth-1);
			break;
		}
		default: break;
	}
};