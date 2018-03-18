#include <iostream>
#include<vector>
#include<chrono>

#include<ff/utils.hpp>

#include "include/genetics/Forest.h"

using namespace ff;

void evolution_cycle(Forest* forest, long tree_no, int depthmax, int threshold,
    int randmax, int generation_no, double err, bool parallel, int nw, bool debug){

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

	//Performing the evolution cycle
	int i = 0;
	double E = err + 1.0;
	Tree* bestTree;
	std::chrono::duration<double> gen_time, overall_time;
	std::chrono::system_clock::time_point start, end, gen_start, gen_end, overall_start, overall_end;
    overall_start = std::chrono::system_clock::now();
    while(E >= err && ++i<=generation_no){
		gen_start = std::chrono::system_clock::now();

		std::vector<Tree*> newTrees;
		int* bestTrees;

		//Selection
        bestTrees = forest->selectBests(x_vals, y_vals, points_no, threshold);

		//Mutation&Crossover
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
        forest->newGeneration(newTrees);

		if(debug){
			bestTree = forest->getBestTree(x_vals, y_vals, points_no);
			E = forest->getBestFitness(x_vals, y_vals, points_no);
			gen_end = std::chrono::system_clock::now();
			gen_time = gen_end - gen_start;

			std::cout << "Generation "<<i<<
			"\n\tTime(s) ---> "<<gen_time.count()<<
			"\n\tBest Tree = "<< bestTree->toString()<<
			"\n\tFitness = "<<E<<
            "\n\n";
		}
    }
	overall_end = std::chrono::system_clock::now();
	overall_time = overall_end - overall_start;

	if(i > generation_no) i--;
    E = forest->getBestFitness(x_vals, y_vals, points_no);
	if(debug){
		bestTree = forest->getBestTree(x_vals, y_vals, points_no);
		std::cout <<
		"\nGENERATION "<<i<<
		"\nBEST TREE = "<<bestTree->toString()<<
		"\nFITNESS = "<<E<<
		"\nOVERALL TIME(s) = "<<overall_time.count()<<"\n";
	}
	else{
		std::cout <<"results"<<
		" nw "<<nw<<" s "<<overall_time.count()<<
		" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
		" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";
	}

	delete forest;
};