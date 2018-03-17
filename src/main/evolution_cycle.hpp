#include <iostream>
#include<vector>
#include<chrono>

#include<ff/utils.hpp>

#include "include/genetics/Forest.h"

using namespace ff;

void evolution_cycle(Forest* forest, long tree_no, int depthmax, int threshold,
    int randmax, int generation_no, double err, bool parallel, int nw=1){

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

	//Performing the evolution cycle
	int i = 0;
	double E = err + 1.0;
	Tree* bestTree;
	std::chrono::duration<double> sel_time, mut_cross_time, newg_time, gen_time, overall_time;
	std::chrono::steady_clock::time_point start, end, gen_start, gen_end, overall_start, overall_end;
	overall_start = std::chrono::steady_clock::now();
    overall_start = std::chrono::steady_clock::now();
    while(E >= err && ++i<=generation_no){
		gen_start = std::chrono::steady_clock::now();
		std::vector<Tree*> newTrees;
		int* bestTrees;

		//Selection
		//ffTime(START_TIME);
		start = std::chrono::steady_clock::now();
        bestTrees = forest->selectBests(x_vals, y_vals, points_no, threshold);
		end = std::chrono::steady_clock::now();
		//ffTime(STOP_TIME);
		//sel_time = ffTime(GET_TIME);
		sel_time = end - start;

		//Mutation&Crossover
		//ffTime(START_TIME);
		start = std::chrono::steady_clock::now();
        for(int j=0; j<threshold; j++){
			int r = std::rand()%3;
			if(r == 0) newTrees.push_back(forest->getTree(bestTrees[j])->copy());
			if(r == 1) newTrees.push_back(forest->mutation(bestTrees[j]));
			if(r == 2) {
				//Extraction without replacement
				int tree1_id, tree2_id;
				tree1_id = bestTrees[j];
				tree2_id = std::rand()%(threshold-1);
				if(tree2_id >= tree1_id) ++tree2_id;
				newTrees.push_back(forest->crossover(tree1_id, tree2_id));
			}
		}
		end = std::chrono::steady_clock::now();
		//ffTime(STOP_TIME);
		//mut_cross_time = ffTime(GET_TIME);
		mut_cross_time = end - start;
		
		//ffTime(START_TIME);
		start = std::chrono::steady_clock::now();
        forest->newGeneration(newTrees);
		end = std::chrono::steady_clock::now();
		//ffTime(STOP_TIME);
		//newg_time = ffTime(GET_TIME);
		newg_time = end - start;

		gen_end = std::chrono::steady_clock::now();
		gen_time = gen_end - gen_start;

		if(i%1 == 0){
			bestTree = forest->getBestTree(x_vals, y_vals, points_no);
			E = forest->getBestFitness(x_vals, y_vals, points_no);
			std::cout << "Generation "<<i<<
			//"\n\tselection ----------> "<<sel_time.count()<<
			//"\n\tmut&cross ----------> "<<mut_cross_time.count()<<
			//"\n\tnew generation -----> "<<newg_time.count()<<
			//"\n\tTime ---> "<<gen_time.count()<<
			//"\n\tBest Tree = "<< bestTree->toString()<<
			//"\n\tFitness = "<<E<<
            "\n";
		}
    }
	overall_end = std::chrono::steady_clock::now();
	overall_time = overall_end - overall_start;

	if(i > generation_no) i--;
	bestTree = forest->getBestTree(x_vals, y_vals, points_no);
    E = forest->getBestFitness(x_vals, y_vals, points_no);
    std::cout <<
    "\nGENERATION "<<i<<
    "\nBEST TREE = "<<bestTree->toString()<<
    "\nFITNESS = "<<forest->fitness(bestTree, x_vals, y_vals, points_no)<<
	"\nOVERALL TIME(s) = "<<overall_time.count()<<"\n";

	delete forest;
};