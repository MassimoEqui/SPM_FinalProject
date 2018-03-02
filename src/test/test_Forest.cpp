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
    int randseed = std::rand(), randmax = 100.0;
    int depthmax = std::atoi(argv[1]);
    std::cout << "TEST FOREST\nforest = new Forest(4, "<<depthmax<<", 4, "
        <<randmax<<", "<<randseed<<");\n\n";
    Forest* forest = new Forest(10, depthmax, 4, randmax, randseed);

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
    forest->selectBests(x_vals, y_vals, 10);
    std::cout << "REPRESENTATION\n";
    std::cout << "tree->toStringBests() =\n"<< forest->toStringBests() <<"\n";

    delete forest;
    return 0;
}