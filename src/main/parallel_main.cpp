#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>
#include<vector>

#include<ff/utils.hpp>

#include "include/genetics/ParallelForest.h"

using namespace ff;

int main(int argc, char const *argv[])
{
	if(argc != 9){
		std::cout << "8 parameters needed\n"<<
			"\t./parallel_main.out tree_no depthmax threshold randmax gen_no err nw_F nw_PF;\n"<<
			"example\n"<<
			"\t./parallel_main.out 1000 5 400 10 100 0.1 4 2\n";	
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
	long tree_no = std::atoi(argv[1]);
	int depthmax = std::atoi(argv[2]);
	int threshold = std::atoi(argv[3]);
	int randmax = std::atoi(argv[4]);
	int generation_no = std::atoi(argv[5]);
	double err = std::atof(argv[6]);
	int nw_F = std::atoi(argv[7]);
	int nw_PF = std::atoi(argv[8]);

	//good parameter setting: 1000 5 400 10 150 150 1000 0.1

	ParallelForest* forest = new ParallelForest(tree_no, depthmax, randmax, nw_F, nw_PF);

	//Performing the evolution cycle
	int i = 0;
	double E = err + 1.0;
	Tree* bestTree;
	double sel_time, mut_cross_time, newg_time;
	sel_time = mut_cross_time = newg_time = -1.0;
    while(E >= err && ++i<=generation_no){
		std::vector<Tree*> newTrees;

		//Selection
		ffTime(START_TIME);
        int* bestTrees = forest->selectBests(x_vals, y_vals, points_no, threshold);
		ffTime(STOP_TIME);
		sel_time = ffTime(GET_TIME);

		//Mutation&Crossover
		ffTime(START_TIME);
        for(int i=0; i<threshold; i++){
			int r = std::rand()%3;
			if(r == 0) newTrees.push_back(forest->getTree(bestTrees[i])->copy());
			if(r == 1) newTrees.push_back(forest->mutation(bestTrees[i]));
			if(r == 2) {
				//Extraction without replacement
				int tree1_id, tree2_id;
				tree1_id = bestTrees[i];
				tree2_id = std::rand()%(threshold-1);
				if(tree2_id >= tree1_id) ++tree2_id;
				newTrees.push_back(forest->crossover(tree1_id, tree2_id));
			}
		}
		ffTime(STOP_TIME);
		mut_cross_time = ffTime(GET_TIME);
		
		ffTime(START_TIME);
        forest->newGeneration(newTrees);
		ffTime(STOP_TIME);
		newg_time = ffTime(GET_TIME);

		if(i%1 == 0){
			bestTree = forest->getBestTree(x_vals, y_vals, points_no);
			E = forest->getBestFitness(x_vals, y_vals, points_no);
			std::cout << "Generation "<<i<<
			"\n\tselection ---> "<<sel_time<<
			"\n\tmut&cross ---> "<<mut_cross_time<<
			"\n\tnew generation ---> "<<newg_time<<
			"\n\tBest Tree = "<< bestTree->toString()<<
			"\n\tFitness = "<<E<<"\n\n";
		}
    }

	if(i > generation_no) i--;
	bestTree = forest->getBestTree(x_vals, y_vals, points_no);
    E = forest->getBestFitness(x_vals, y_vals, points_no);
    std::cout << "\nGENERATION "<<i<<
	"\nBEST TREE = "<<bestTree->toString()<<
	"\nFITNESS = "<<E<<"\n";

	delete forest;
	return 0;
}