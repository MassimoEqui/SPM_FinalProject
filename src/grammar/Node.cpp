#include "include/grammar/Node.h"

double Node::evaluate(){
	return 0.0;
};

INode* Node::expand(int p_id){
	return new Node();
}