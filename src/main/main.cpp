#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/genetics/Forest.h"


int main(int argc, char const *argv[])
{
	if(argc != 9){
		std::cerr << "Wrong argument number\n";
		return 1;
	}

	//Setting the rand() environment
	std::srand(std::time(nullptr));


	//Reading pairs (x,f(x)) from stdin (usually from a file)
	int points_no;
	double *x_vals, *y_vals;
	std::cin >> points_no;
	x_vals = new double[points_no];
	y_vals = new double[points_no];

	for(int i=0; i<points_no; i++)
		std::cin >> x_vals[i];
	
	for(int i=0; i<points_no; i++)
		std::cin >> y_vals[i];

	//Generating a new pool of functions (trees)
	int tree_no, depthmax, threshold, randmax, randseed, mutation_no, crossover_no, generation_no;
	double E, err;
	tree_no = std::atoi(argv[1]);
	depthmax = std::atoi(argv[2]);
	threshold = std::atoi(argv[3]);
	randmax = std::atoi(argv[4]);
	mutation_no = std::atoi(argv[5]);
	crossover_no = std::atoi(argv[6]);
	generation_no = std::atoi(argv[7]);
	err = std::atof(argv[8]);

	//good parameter setting: 1000 5 400 10 150 150 1000 0.1

	randseed = std::rand();
	Forest* forest = new Forest(tree_no, depthmax, threshold, randmax, randseed);

	//Performing the evolution cycle
	int i = 0;
	E = err + 1.0;
	Tree* bestTree;
    while(E >= err && i++<generation_no){
		//Selection
        int* bestTrees = forest->selectBests(x_vals, y_vals, points_no);
		//Mutation
        for(int i=0; i<mutation_no; i++)
            forest->mutation(bestTrees[std::rand()%threshold]);
		//Crossover
        for(int i=0; i<crossover_no; i++)
            forest->crossover(bestTrees[std::rand()%threshold], bestTrees[std::rand()%threshold]);
		//New generation
        forest->newGeneration(bestTrees);
		bestTree = forest->getBest(x_vals, y_vals, points_no);
    	E = forest->fitness(bestTree, x_vals, y_vals, points_no);
		if(i%25 == 0) std::cout << "generation "<<i<<"\n";
    }

	bestTree = forest->getBest(x_vals, y_vals, points_no);
    E = forest->fitness(bestTree, x_vals, y_vals, points_no);
    std::cout << "GENERATION "<<i-1<<"\nBEST TREE = ";
    bestTree = forest->getBest(x_vals, y_vals, points_no);
    std::cout << bestTree->toString();
    std::cout << "\nFITNESS = "<<forest->fitness(bestTree, x_vals, y_vals, points_no) << "\n";

	return 0;
}