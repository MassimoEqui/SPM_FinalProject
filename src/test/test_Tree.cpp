#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/genetics/Tree.h"
#include "include/genetics/Forest.h"
#include "include/grammar/grammar.h"

void printRepresentation(Tree* tree, std::string name, double x_val){
    std::cout << name+"->toString() = "<< tree->toString() <<"\n";
    std::cout << name+"->evaluate("<<x_val<<") = " << tree->evaluate(x_val) << "\n";
    std::cout << name+"->getDepth() = "<< tree->getDepth() <<"\n";
};

int main(int argc, char const *argv[]){/*
    std::srand(std::time(nullptr));
    int randmax = 100.0;
    int depth = std::atoi(argv[1]);
    Tree* tree = new Tree(depth, randmax);
    std::cout << "TEST TREE\ntree = new Tree("<<depth<<", "<<randmax<<");\n\n";

    std::cout << "REPRESENTATION\n";
    printRepresentation(tree, "tree", 1.0);

    //Tree->mutation(...)
    for(int i=0; i<=depth; i++){
        std::cout << "\nOPERATION: tree->mutation("<<depth-i<<");\n";
        tree->mutation(depth-i);
        std::cout << "REPRESENTATION\n";
        printRepresentation(tree, "tree", 1.0);
    }

    //Tree->copy(...)
    std::cout << "\nOPERATION: tree->copy();\n";
    Tree* tree_1 = tree->copy();
    std::cout << "REPRESENTATION\n";
    printRepresentation(tree, "tree", 1.0);
    delete tree;
    std::cout << "\n";
    printRepresentation(tree_1, "tree_1", 1.0);

    delete tree_1;*/

    Forest* forest = new Forest(0, 5, 10);
    //node
    Node* r = new Node(10);
    //[ node - node ]
    INode** r_children = r->expandByOne(_NODE_THIRD_PROD, MIN);
    Node* rc0 = (Node*)r_children[0];
    Node* rc1 = (Node*)r_children[1];
    //[ cos(node) - node ]
    INode** rc0_children = rc0->expandByOne(_NODE_SECOND_PROD, COS);
    Node* rc0c0 = (Node*)rc0_children[0];
    //[ cos(node) - [ node^node ] ]
    INode** rc1_children = rc1->expandByOne(_NODE_THIRD_PROD, POW);
    Node* rc1c0 = (Node*)rc1_children[0];
    Node* rc1c1 = (Node*)rc1_children[1];
    //[ cos(leaf) - [ node^node ] ]
    INode** rc0c0_children = rc0c0->expandByOne(_NODE_FIRST_PROD, -1);
    Leaf* rc0c0c0 = (Leaf*)rc0c0_children[0];
    //[ cos(leaf) - [ leaf^node ] ]
    INode** rc1c0_children = rc1c0->expandByOne(_NODE_FIRST_PROD, -1);
    Leaf* rc1c0c0 = (Leaf*)rc1c0_children[0];
    //[ cos(leaf) - [ leaf^leaf ] ]
    INode** rc1c1_children = rc1c1->expandByOne(_NODE_FIRST_PROD, -1);
    Leaf* rc1c1c0 = (Leaf*)rc1c1_children[0];
    //[ cos(x)-[ leaf^leaf ] ]
    rc0c0c0->expandLast(_LEAF_SECOND_PROD, -1);
    //[ cos(x)-[ x^leaf ] ]
    rc1c0c0->expandLast(_LEAF_SECOND_PROD, -1);
    //[ cos(x)-[ x^3 ] ]
    rc1c1c0->expandLast(_LEAF_FIRST_PROD, 3);

    Tree* tree = new Tree(2,10);
    tree->setRoot(r);
    std::cout << "\nDESIRED TREE: [ cos(x)-[ x^3 ] ]\n";
    std::cout << "REPRESENTATION\n";
    printRepresentation(tree, "tree", 1.0);

    long points_no;
	double *x_vals, *y_vals;
	std::cin >> points_no;
	x_vals = new double[points_no];
	y_vals = new double[points_no];

	for(int i=0; i<points_no; i++)
		std::cin >> x_vals[i];
	
	for(int i=0; i<points_no; i++)
		std::cin >> y_vals[i];

	for(int i=0; i<points_no; i++)
		std::cout << "DEBUG:******\n"<<(y_vals[i]-tree->evaluate(x_vals[i])) << "\nDEBUG:******\n";

    return 0;
}