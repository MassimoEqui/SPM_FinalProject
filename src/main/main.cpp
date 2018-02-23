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
	INode* expr = new Const(4.16);
	std::cout << "(Const)expr value = " << expr->evaluate() << "\n";
	delete expr;

	//Test Var
	Var* var = new Var();
	var->setValue(3.14);
	expr = var;	
	std::cout << "(Var)expr value = " << expr->evaluate() << "\n";
	delete expr;

	//Test Leaf
	Leaf* leaf = new Leaf(100.0, std::rand());
	expr = leaf;
	expr->expand(0);
	std::cout << "(Leaf)expr value = " << expr->evaluate() << "\n";
	delete expr;

	//Test Node
	Node* node = new Node(1000.0, std::rand());
	expr = node;
	expr->expand(0);
	std::cout << "(Node)expr value = " << expr->evaluate() << "\n";
	delete expr;

	//getchar();
	return 0;
}