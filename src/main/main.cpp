#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/grammar/Const.h"
#include "include/grammar/Var.h"
#include "include/grammar/Leaf.h"
#include "include/grammar/Node.h"

//using namespace std;

int main(int argc, char const *argv[])
{
	//Setting the rand() environment
	std::srand(std::time(nullptr));

	//Test Const
	std::cout << "TEST: Const\n";
	Const* cnst = new Const(4.16);
	std::cout << "(Const)cnst string = " << cnst->toString() << "\n";
	std::cout << "(Const)cnst value = " << cnst->evaluate() << "\n\n";
	delete cnst;

	//Test Var
	std::cout << "TEST: Var\n";
	Var* var = new Var();
	var->setValue(3.14);
	std::cout << "(Var)var string = " << var->toString() << "\n";
	std::cout << "(Var)var value = " << var->evaluate() << "\n\n";
	delete var;

	//Test Leaf (deterministic)
	std::cout << "TEST: Leaf (deterministic)\n";
	Leaf* leaf = new Leaf(100.0, std::rand());
	leaf->expandLast(1,1.23);
	std::cout << "(Leaf,p_id=1,c=1.23)leaf string = " << leaf->toString() << "\n";
	std::cout << "(Leaf,p_id=1,c=1.23)leaf value = " << leaf->evaluate() << "\n";
	leaf->expandLast(2,0.0);
	std::cout << "(Leaf,p_id=2,c=0.0)leaf string = " << leaf->toString() << "\n";
	std::cout << "(Leaf,p_id=2,c=0.0)leaf value = " << leaf->evaluate() << "\n\n";	

	//Test Leaf (random)
	std::cout << "TEST: Leaf (random)\n";
	leaf->expand(0);
	std::cout << "(Leaf,p_id=rand())leaf string = " << leaf->toString() << "\n";
	std::cout << "(Leaf,p_id=rand())leaf value = " << leaf->evaluate() << "\n\n";
	delete leaf;

	//Test Node (deterministic)
	std::cout << "TEST: Node (deterministic)\n";
/*
	Node* node_1 = new Node(1000.0,std::rand());
	INode** children_1 = node_1->expandByOne(3,PLUS);
	Node* node_1a = (Node*)children_1[0];
	Node* node_1b = (Node*)children_1[1];
	INode** children_1a = node_1a->expandByOne(2,EXP);
	INode** children_1b = node_1b->expandByOne(2,SIN);
	Node* node_1aa = (Node*)children_1a[0];
	Node* node_1bb = (Node*)children_1b[0];
	INode** children_1aa = node_1aa->expandByOne(1,-1);
	INode** children_1bb = node_1bb->expandByOne(1,-1);
	Leaf* leaf_1aa = (Leaf*)children_1aa[0];
	Leaf* leaf_1bb = (Leaf*)children_1bb[0];
	leaf_1aa->expandLast(1,5.67);
	leaf_1bb->expandLast(2,0.0);
	std::cout << "(Node_1,p_id=3,depth=1)node string = " << node_1->toString() << "\n";
	std::cout << "(Node_1,p_id=3,depth=1)node value = " << node_1->evaluate() << "\n\n";
*/
	Node* node_1 = new Node(1000.0,std::rand());
	INode** children_1 = node_1->expandByOne(3,PLUS);
	((Leaf*)
	((Node*)
	((Node*)children_1[0])->
	expandByOne(2,EXP)[0])->
		expandByOne(1,-1)[0])->
			expandLast(2,0.0);
	((Leaf*)((Node*)((Node*)children_1[1])->
	expandByOne(2,SIN)[0])->
		expandByOne(1,-1)[0])->
			expandLast(1,5.67);
	std::cout << "(Node_1)node string = " << node_1->toString() << "\n";
	std::cout << "(Node_1)node value = " << node_1->evaluate() << "\n\n";
	delete node_1;

	node_1 = new Node(1000.0,std::rand());
	children_1 = node_1->expandByOne(3,TIMES);
	((Leaf*)
	((Node*)
	((Node*)children_1[0])->
	expandByOne(2,SIN)[0])->
		expandByOne(1,-1)[0])->
			expandLast(2,0.0);
	INode** children_12 = ((Node*)children_1[1])->expandByOne(3,POW);
	((Leaf*)
	((Node*)children_12[0])->
	expandByOne(1,-1)[0])->
		expandLast(2,0.0);
	((Leaf*)
	((Node*)children_12[1])->
	expandByOne(1,-1)[0])->
		expandLast(1,2.0);
	std::cout << "(Node_1)node string = " << node_1->toString() << "\n";
	std::cout << "(Node_1)node value = " << node_1->evaluate() << "\n\n";
	delete node_1;

	//Test Node (random)
	std::cout << "TEST: Node (random)\n";
	Node* node = new Node(1000.0, std::rand());
	for(int i=0; i<5; i++){
		std::cout <<"Depth="<<i<<"\n";
		node->expand(i);
		std::cout << "(Node,p_id=rand(),depth="<<i<<")node string = " << node->toString() << "\n";
		std::cout << "(Node,p_id=rand(),depth="<<i<<")node value = " << node->evaluate() << "\n\n";
	};/*
	node->expand(2);
	std::cout << "(Node,p_id=rand(),depth=2)node string = " << node->toString() << "\n";
	std::cout << "(Node,p_id=rand(),depth=2)node value = " << node->evaluate() << "\n\n";
	node->expand(3);
	std::cout << "(Node,p_id=rand(),depth=3)node string = " << node->toString() << "\n";
	std::cout << "(Node,p_id=rand(),depth=3)node value = " << node->evaluate() << "\n";*/
	delete node;

	//getchar();
	return 0;
}