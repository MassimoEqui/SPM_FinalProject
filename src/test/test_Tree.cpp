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
    int randseed = std::rand(), randmax = 100.0;
    int depth = std::atoi(argv[1]);
    Tree* tree = new Tree(depth, randmax, randseed);
    std::cout << "TEST TREE\ntree = new Tree("<<depth<<", "<<randmax<<", "<<randseed<<");\n\n";

    std::cout << "REPRESENTATION\n";
    printRepresentation(tree, "tree", 1.0);

    //Tree->mutation(...)
    for(int i=0; i<=depth; i++){
        std::cout << "\nOPERATION: tree->mutation("<<depth-i<<");\n";
        tree->mutation(depth-i);
        std::cout << "REPRESENTATION\n";
        printRepresentation(tree, "tree", 1.0);
    }

    delete tree;

    return 0;
}