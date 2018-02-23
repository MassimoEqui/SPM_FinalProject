#include "include/grammar/Node.h"

#include<cstdlib>
#include<ctime>

#include "include/grammar/Leaf.h"

Node::Node(double randmax, int randseed){
	std::srand(randseed);
	this->randmax = randmax;
	this->p_id = -1;
	for(int i=0; i<CHILDREN_NUM; i++)
		this->children[i] = nullptr;
};

Node::~Node(){
	for(int i=0; i<CHILDREN_NUM; i++)
		if(children[i] != nullptr)
			delete children[i];
}

double Node::evaluate(){
	if(this->p_id==1)
		return this->children[0]->evaluate();
	return 0.0;
};

void Node::expand(int depth){
	if(depth < 0)
		return;		
	if(depth == 0)
		this->p_id = 1;
	else
		this->p_id = 2 + (std::rand() % (_NODE_PROD_NUM-1));

	for(int i=0; i<CHILDREN_NUM; i++)
		if(children[i] != nullptr)
			delete children[i];
	

	switch(this->p_id){
		case 1: {
			children[0] = new Leaf(this->randmax, std::rand());
			children[0]->expand(0);
			break;
		}
		case 2: {
			//TODO
		}
		default: break;
	}
};