#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include<ff/utils.hpp>

#include "include/parallel_genetics/ParallelForest.h"

using namespace ff;

/*
Emitter

Worker

Collector : public ff_node{
	
}
*/

int main(int argc, char const *argv[])
{
	if(argc != 9){
		std::cout << "8 parameters needed\n";
		std::cout << "\t./parallel_main.out tree_no depthmax threshold randmax mut_no cross_no gen_no;\n";
		std::cout << "example\n";
		std::cout << "\t./parallel_main.out 1000 5 400 10 150 150 100 0.1\n";	
		return 0;
	}

	//Setting the rand() environment
	std::srand(std::time(nullptr));

	//Reading pairs (x,f(x)) from stdin (usually from a file)
	long points_no;
	double *x_vals, *y_vals;
	std::cin >> points_no;
	x_vals = new double[points_no];
	y_vals = new double[points_no];

	for(int i=0; i<points_no; i++)
		std::cin >> x_vals[i];
	
	for(int i=0; i<points_no; i++)
		std::cin >> y_vals[i];

	std::cout << "input data loaded\n";
	
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
	ParallelForest* forest = new ParallelForest(tree_no, depthmax, threshold, randmax, randseed);

	//DEBUG: Selection
	//int* bestTrees = forest->selectBests(x_vals, y_vals, points_no);


	//Performing the evolution cycle
	int i = 0;
	E = err + 1.0;
	ParallelTree* bestTree;
	double sel_time, mut_time, cross_time, newg_time;
	sel_time = mut_time = cross_time = newg_time = -1.0;
    while(E >= err && ++i<=generation_no){
		//Selection
		ffTime(START_TIME);
        int* bestTrees = forest->selectBests(x_vals, y_vals, points_no);
		ffTime(STOP_TIME);
		sel_time = ffTime(GET_TIME);
		
		//Mutation
		ffTime(START_TIME);
        for(int i=0; i<mutation_no; i++)
            forest->mutation(bestTrees[std::rand()%threshold]);
		ffTime(STOP_TIME);
		mut_time = ffTime(GET_TIME);

		//Crossover
		ffTime(START_TIME);
        for(int i=0; i<crossover_no; i++)
            forest->crossover(bestTrees[std::rand()%threshold], bestTrees[std::rand()%threshold]);
		ffTime(STOP_TIME);
		cross_time = ffTime(GET_TIME);

		//New generation
		ffTime(START_TIME);
        forest->newGeneration(bestTrees);
		ffTime(STOP_TIME);
		newg_time = ffTime(GET_TIME);

		if(i%1 == 0){
			std::cout << "Generation "<<i<<
			"\n\tselection ---> "<<sel_time<<"\n\tmutation ---> "<<mut_time<<
			"\n\tcrossover ---> "<<cross_time<<"\n\tnew generation ---> "<<newg_time<<"\n";
		}

		bestTree = forest->getBest(x_vals, y_vals, points_no);
    	E = forest->fitness(bestTree, x_vals, y_vals, points_no);
    }

	if(i > generation_no) i--;
	bestTree = forest->getBest(x_vals, y_vals, points_no);
    E = forest->fitness(bestTree, x_vals, y_vals, points_no);
    std::cout << "\nGENERATION "<<i<<"\nBEST TREE = ";
    bestTree = forest->getBest(x_vals, y_vals, points_no);
    std::cout << bestTree->toString();
    std::cout << "\nFITNESS = "<<forest->fitness(bestTree, x_vals, y_vals, points_no) << "\n";

	delete forest;
	return 0;
}