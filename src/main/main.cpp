#include <iostream>
#include <stdio.h>

#include "include/grammar/Node.h"
#include "include/grammar/Const.h"
#include "include/grammar/Var.h"

using namespace std;

int main(int argc, char const *argv[])
{
	INode* expr = new Const(4.16);
	cout << "Expr value = " << expr->evaluate() << "\n";
	delete expr;
	Var* var = new Var();
	var->setValue(3.14);
	expr = var;	
	cout << "Expr value = " << expr->evaluate() << "\n";
	//getchar();
	return 0;
}