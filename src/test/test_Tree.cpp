#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/genetics/Tree.h"
#include "include/grammar/grammar.h"

void printRepresentation(Tree* tree, std::string name, double x_val){
    std::cout << name+"->toString() = "<< tree->toString() <<"\n";
    std::cout << name+"->evaluate("<<x_val<<") = " << tree->evaluate(x_val) << "\n";
    std::cout << name+"->getDepth() = "<< tree->getDepth() <<"\n";
};

int main(int argc, char const *argv[]){
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

    delete tree_1;

    return 0;
}