#include "include/grammar/Node.h"

#include<cstdlib>
#include<ctime>
#include<cmath>
#include<limits>

#include "include/grammar/Leaf.h"

Node::Node(double randmax){
	this->randmax = randmax;
	this->p_id = -1;
	this->unop = -1;
	this->binop = -1;
	this->children_num = 0;
	for(int i=0; i<CHILDREN_NUM; i++)
		this->children[i] = nullptr; 
};

Node::~Node(){
	for(int i=0; i<CHILDREN_NUM; i++)
		if(children[i] != nullptr)
			delete children[i];
}

void Node::setParameters(int p_id, int unop, int binop, int children_num){
	this->p_id = p_id;
	this->unop = unop;
	this->binop = binop;
	this->children_num = children_num;
};

double Node::evaluate(double x_val){
	switch(this->p_id){
		case _NODE_FIRST_PROD: return this->children[0]->evaluate(x_val);
		case _NODE_SECOND_PROD: {
			switch(this->unop){
				case EXP :{	return std::exp(this->children[0]->evaluate(x_val)); }
				case SIN :{	return std::sin(this->children[0]->evaluate(x_val)); }
				case COS :{	return std::cos(this->children[0]->evaluate(x_val)); }
				case LOG :{	return std::log(this->children[0]->evaluate(x_val)); }
				default : return -1.0;
			}			
		}
		case _NODE_THIRD_PROD: {
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
		default : return -1.0;
	}
};

void Node::expandRandom(int depth){
	int children_depth = depth-1;	
	if(depth < 0)
		return;
	if(depth == 0){
		this->p_id = _NODE_FIRST_PROD;
		children_depth = 0;
	}
	else
		this->p_id = _NODE_SECOND_PROD + (std::rand() % (_NODE_PROD_NUM-1));
	
	int op = -1;
	switch(this->p_id){
		case _NODE_FIRST_PROD:{ op = -1; break; }
		case _NODE_SECOND_PROD:{ op = EXP + (std::rand() % _UNOP_PROD_NUM);	break; }
		case _NODE_THIRD_PROD:{ op = MIN + (std::rand() % _BINOP_PROD_NUM); break; }
		default:{ op = -1; break; }
	}

	INode** children = this->expandByOne(this->p_id,op);
	delete children;
	for(int i=0; i<CHILDREN_NUM; i++)
		if(this->children[i] != nullptr)
			this->children[i]->expandRandom(children_depth);
};

INode** Node::expandByOne(int p_id, int op){
	if(p_id<_NODE_FIRST_PROD || p_id>_NODE_PROD_NUM)
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
		case _NODE_FIRST_PROD: {//<leaf>
			this->children_num = 1;
			this->children[0] = new Leaf(this->randmax);
			break;
		}
		case _NODE_SECOND_PROD: {//<unop> <node>
			this->children_num = 1;
			this->unop = op;
			this->children[0] = new Node(this->randmax);
			break;
		}
		case _NODE_THIRD_PROD: {//<node> <binop> <node>
			this->children_num = 2;
			this->binop = op;
			this->children[0] = new Node(this->randmax);
			this->children[1] = new Node(this->randmax);
			break;
		}
		default: break;
	}

	return this->getChildren();
};

std::string Node::toString(){
	std::string s = "";  
	switch(this->p_id){
		case _NODE_FIRST_PROD: {
			s = this->children[0]->toString();
			break;
		}
		case _NODE_SECOND_PROD: {
			switch(this->unop){
				case EXP :{ s = "exp"; break; }
				case SIN :{	s = "sin"; break; }
				case COS :{ s = "cos"; break; }
				case LOG :{	s = "log"; break; }
				default : break;
			}
			if(!s.empty())
				s = s + "("+this->children[0]->toString()+")";
			break;			
		}
		case _NODE_THIRD_PROD: {
			switch(this->binop){
				case MIN :{	s = "-"; break;	}
				case PLUS :{ s = "+"; break; }
				case TIMES :{ s = "*"; break; }
				case DIV :{	s = "/"; break;	}
				case POW :{	s = "^"; break;	}
				default : break;
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

INode** Node::getChildren(){
	INode** chldr = new INode*[CHILDREN_NUM];
	for(int i=0; i<CHILDREN_NUM; i++)
		chldr[i] = this->children[i];
	return chldr;
};

int Node::getChildrenNum(){ return this->children_num; };


INode* Node::setChild(int child_id, INode* child){
	if(child_id < 0 || child_id >= this->children_num)
		return nullptr;
	INode* oldChild = this->children[child_id];
	this->children[child_id] = child;
	return oldChild;
};

INode* Node::copyToEnd(){
	Node* newNode = new Node(this->randmax);
	newNode->setParameters(this->p_id, this->unop, this->binop, this->children_num);
	for(int i=0; i<this->children_num; i++)
		newNode->setChild(i, this->children[i]->copyToEnd());
	return newNode;
};