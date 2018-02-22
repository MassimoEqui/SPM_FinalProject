#include <iostream>
#include <stdio.h>

#include "include/grammar/Const.h"
#include "include/grammar/Var.h"
#include "include/grammar/Leaf.h"
#include "include/grammar/Node.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//Test Const
	INode* expr = new Const(4.16);
	cout << "(Const)expr value = " << expr->evaluate() << "\n";
	delete expr;

	//Test Var
	Var* var = new Var();
	var->setValue(3.14);
	expr = var;	
	cout << "(Var)expr value = " << expr->evaluate() << "\n";
	delete expr;

	//Test
	Leaf* leaf = new Leaf(100.0);
	expr = leaf;
	expr->expand(1,2);
	cout << "(Leaf, p_id=1)expr value = " << expr->evaluate() << "\n";

	expr->expand(2,2);
	cout << "(Leaf, p_id=2)expr value = " << expr->evaluate() << "\n";

	//getchar();
	return 0;
}