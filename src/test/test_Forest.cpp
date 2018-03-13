#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include "include/genetics/Forest.h"
#include "include/grammar/grammar.h"

void printRepresentation(Forest* forest, std::string name){
    std::cout << name+"->toString() =\n"<< forest->toString() <<"\n";
    //std::cout << name+"->evaluate("<<x_val<<") = " << forest->evaluate(x_val) << "\n";
};

int main(int argc, char const *argv[]){
    std::srand(std::time(nullptr));
    int randmax = 100.0;
    int depthmax = std::atoi(argv[1]);
    int threshold = 4;
    std::cout << "TEST FOREST\nforest = new Forest(10, "<<depthmax<<", 4, "
        <<randmax<<");\n\n";
    Forest* forest = new Forest(10, depthmax, randmax);

    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");
    
    std::cout << "\nOPERATION: forest->crossover(3, 7);\n";
    forest->crossover(3, 7);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");

    std::cout << "\nOPERATION: forest->mutation(5);\n";
    forest->mutation(5);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");

    double x_vals[10] = {1.1, 2.89, 34.56, 45.654, 78.75, 123.456, 198.3426, 294.45, 357.865};
    double y_vals[10] = {2.331, 25.1376, 41279.2, 95157.1, 488374, 1.88164e+06,
                            7.80276e+06, 2.55291e+07, 4.58308e+07, 1};
    std::cout << "\nOPERATION: forest->selectBests(x_vals, y_vals, pointsNum);\n";
    int* bestTrees = forest->selectBests(x_vals, y_vals, 10);
    std::cout << "REPRESENTATION\n";    
    std::string s = "";
    for(int i=0; i<threshold; i++)
        s = s+"\n\nTree [ "+std::to_string(bestTrees[i])+" ]\n"+forest->toStringTree(bestTrees[i]);
    s += "\n\n";
    std::cout << s;

    std::cout << "\nOPERATION: forest->newGeneration(bestTrees);\n";
    forest->newGeneration(bestTrees);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");

    delete forest;


    std::cout << "TEST FOREST\nforest = new Forest(10, "<<depthmax<<", 4, "
        <<randmax<<");\n\n";
    forest = new Forest(10, depthmax, randmax);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");

    std::cout << "\nOPERATION: complete cycle of evolution;\n";
    bestTrees = forest->selectBests(x_vals, y_vals, 10);
    for(int i=0; i<3; i++)
        forest->mutation(bestTrees[std::rand()%threshold]);
    for(int i=0; i<3; i++)
        forest->crossover(bestTrees[std::rand()%threshold], bestTrees[std::rand()%threshold]);
    forest->newGeneration(bestTrees);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");

    delete forest;

    return 0;
}