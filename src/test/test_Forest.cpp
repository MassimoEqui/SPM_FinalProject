#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/genetics/Forest.h"
#include "include/grammar/grammar.h"

void printRepresentation(Forest* forest, std::string name){
    std::cout << name+"->toString() =\n"<< forest->toString() <<"\n";
    //std::cout << name+"->evaluate("<<x_val<<") = " << forest->evaluate(x_val) << "\n";
};

int main(int argc, char const *argv[]){
    std::srand(std::time(nullptr));
    int randseed = std::rand(), randmax = 100.0;
    int depthmax = std::atoi(argv[1]);
    Forest* forest = new Forest(10, depthmax, 4, randmax, randseed);
    std::cout << "TEST FOREST\nforest = new Forest(4, "<<depthmax<<", 4, "
        <<randmax<<", "<<randseed<<");\n\n";

    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");
    
    std::cout << "\nOPERATION: forest->crossover(2, 3, 7);\n";
    forest->crossover(2, 3, 7);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");
    std::cout << "DEBUG: *****************\n";
    delete forest;
/*
    std::cout << "REPRESENTATION\n";
    printRepresentation(tree, "tree", 1.0);

    //Tree->mutation(...)
    for(int i=0; i<depth; i++){
        std::cout << "\nOPERATION: tree->mutation("<<i<<");\n";
        tree->mutation(i);
        std::cout << "REPRESENTATION\n";
        printRepresentation(tree, "tree", 1.0);
    }

    delete tree;
*/
    return 0;
}