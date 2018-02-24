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
	INode* expr = new Const(4.16);
	std::cout << "(Const)expr value = " << expr->evaluate() << "\n\n";
	delete expr;

	//Test Var
	std::cout << "TEST: Var\n";
	Var* var = new Var();
	var->setValue(3.14);
	expr = var;	
	std::cout << "(Var)expr value = " << expr->evaluate() << "\n\n";
	delete expr;

	//Test Leaf (deterministic)
	std::cout << "TEST: Leaf (deterministic)\n";
	Leaf* leaf = new Leaf(100.0, std::rand());
	expr = leaf;
	expr->expand(1,0);
	std::cout << "(Leaf,p_id=1)expr value = " << expr->evaluate() << "\n";
	expr->expand(2,0);
	std::cout << "(Leaf,p_id=2)expr value = " << expr->evaluate() << "\n\n";	

	//Test Leaf (random)
	std::cout << "TEST: Leaf (random)\n";
	expr->expand(0);
	std::cout << "(Leaf,p_id=rand())expr value = " << expr->evaluate() << "\n\n";
	delete expr;

	//Test Node (deterministic)
	std::cout << "TEST: Node (deterministic)\n";
	Node* node = new Node(1000.0, std::rand());
	expr = node;
	expr->expand(1,0);
	std::cout << "(Node,p_id=1)expr value = " << expr->evaluate() << "\n\n";

	//Test Node (random)
	std::cout << "TEST: Node (random)\n";
	expr->expand(0);
	std::cout << "(Node,p_id=rand())expr value = " << expr->evaluate() << "\n";
	delete expr;

	//getchar();
	return 0;
}