#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include "include/genetics/Forest.h"
#include "include/grammar/grammar.h"

void printRepresentation(Forest* forest, std::string name){
    std::cout << name+"->toString() =\n"<< forest->toString() <<"\n";
};

void printRepresentation(Forest* forest, int* bestTrees, int threshold){
    for(int i=0; i<threshold; i++)
        std::cout << "Tree [ "<<std::to_string(bestTrees[i])+" ]\n"
                    <<forest->toStringTree(bestTrees[i])<<"\n\n";
};

int main(int argc, char const *argv[]){
    if(argc != 4)
        std::cerr << "Wrong number of arguments\n";

    std::srand(std::time(nullptr));
    int randseed = std::rand(), randmax = 10.0;
    int treeNum = std::atoi(argv[1]);
    int depthmax = std::atoi(argv[2]);
    int threshold = std::atoi(argv[3]);
    std::cout << "TEST FOREST\nforest = new Forest(treeNum="<<treeNum<<", depthmax="<<depthmax
                <<", threshold="<<threshold<<", randmax="<<randmax<<", randseed="<<randseed<<");\n\n";
    Forest* forest = new Forest(treeNum, depthmax, threshold, randmax, randseed);
/*
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");
/*
    double x_vals[10] = {1.1, 2.89, 34.56, 45.654, 78.75, 123.456, 198.3426, 294.45, 357.865};
    double y_vals[10] = {2.331, 25.1376, 41279.2, 95157.1, 488374, 1.88164e+06,
                            7.80276e+06, 2.55291e+07, 4.58308e+07, 1};
*/
    //Reading the input values
    int points_num;
    double *x_vals, *y_vals;
    std::cin >> points_num;
    x_vals = new double[points_num];
    y_vals = new double[points_num];

    for(int i=0; i<points_num; i++)
        std::cin >> x_vals[i];
    
    for(int i=0; i<points_num; i++)
        std::cin >> y_vals[i];

    //Full cycle
    std::cout << "OPERATION: forest->selectBests(x_vals, y_vals, POINTS_NUM);\n";
    int* bestTrees = forest->selectBests(x_vals, y_vals, points_num);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, bestTrees, threshold);
    for(int i=0; i<3; i++)
        forest->mutation(bestTrees[std::rand()%threshold]);
    for(int i=0; i<3; i++)
        forest->crossover(bestTrees[std::rand()%threshold], bestTrees[std::rand()%threshold]);
    forest->newGeneration(bestTrees);
    std::cout << "OPERATION: forest->newGeneration(bestTrees)[after mutation and crossover];\n";
    bestTrees = forest->selectBests(x_vals, y_vals, points_num);
    std::cout << "REPRESENTATION: ALL\n";
    printRepresentation(forest, "forest");
    std::cout << "REPRESENTATION: BESTS\n";
    printRepresentation(forest, bestTrees, threshold);
    std::cout << "REPRESENTATION: BEST TREE\n";
    Tree* bestTree = forest->getBest(x_vals, y_vals, points_num);
    std::cout << bestTree->toString();
    std::cout << "\nFITNESS = "<<forest->fitness(bestTree, x_vals, y_vals, points_num) << "\n";

    std::cout << "\n\nEVOLUTION TEST\n";
    forest = new Forest(treeNum, depthmax, threshold, randmax, randseed);
    std::cout << "\nGENERATION 0\nBEST TREE = ";
    bestTree = forest->getBest(x_vals, y_vals, points_num);
    std::cout << bestTree->toString();
    double oldE = forest->fitness(bestTree, x_vals, y_vals, points_num);
    std::cout << "\nFITNESS = "<<oldE << "\n";
    for(int i=0; i<100; i++){        
        bestTrees = forest->selectBests(x_vals, y_vals, points_num);
        for(int i=0; i<threshold/3; i++)
            forest->mutation(bestTrees[std::rand()%threshold]);
        for(int i=0; i<threshold/3; i++)
            forest->crossover(bestTrees[std::rand()%threshold], bestTrees[std::rand()%threshold]);
        forest->newGeneration(bestTrees);

        bestTree = forest->getBest(x_vals, y_vals, points_num);
        double E = forest->fitness(bestTree, x_vals, y_vals, points_num);
        std::cout << "GENERATION "<<i+1<<"\n";
        if(E < oldE){
            bestTree = forest->getBest(x_vals, y_vals, points_num);
            std::cout << "BEST TREE = "<<bestTree->toString();
            std::cout << "\nFITNESS = "<<forest->fitness(bestTree, x_vals, y_vals, points_num) << "\n";
            oldE = E;
        }
    }

    bestTree = forest->getBest(x_vals, y_vals, points_num);
    double E = forest->fitness(bestTree, x_vals, y_vals, points_num);
    std::cout << "\nGENERATION "<<100<<"\nBEST TREE = ";
    bestTree = forest->getBest(x_vals, y_vals, points_num);
    std::cout << bestTree->toString();
    std::cout << "\nFITNESS = "<<forest->fitness(bestTree, x_vals, y_vals, points_num) << "\n";


/*
    double x_vals[POINTS_NUM] = {1.1, 2.89, 34.56, 45.654, 78.75, 123.456, 198.3426, 294.45, 357.865};
    double y_vals[POINTS_NUM] = {1.1, 2.89, 34.56, 45.654, 78.75, 123.456, 198.3426, 294.45, 357.865};

    std::cout << "\nREAL FUNCTION: f(x) = 2x\n";
    std::cout << "OPERATION: forest->selectBests(x_vals, y_vals, POINTS_NUM);\n";
    int* bestTrees = forest->selectBests(x_vals, y_vals, POINTS_NUM);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, bestTrees, threshold);
/*
    std::cout << "\nOPERATION: complete cycle of evolution;\n";
    int* bestTrees = forest->selectBests(x_vals, y_vals, 10);
    for(int i=0; i<3; i++)
        forest->mutation(bestTrees[std::rand()%threshold]);
    for(int i=0; i<3; i++)
        forest->crossover(bestTrees[std::rand()%threshold], bestTrees[std::rand()%threshold]);
    forest->newGeneration(bestTrees);
    std::cout << "REPRESENTATION\n";
    printRepresentation(forest, "forest");
*/
    delete forest;

    return 0;
}