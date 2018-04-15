#include <iostream>
#include<vector>
#include<chrono>

#include<ff/utils.hpp>

#include "include/genetics/Forest.h"
#include "include/genetics/TestForest.h"

using namespace ff;

long read_input(double** _x_vals, double** _y_vals){
	long points_no;
	double *x_vals, *y_vals;
	std::cin >> points_no;
	x_vals = new double[points_no];
	y_vals = new double[points_no];

	for(int i=0; i<points_no; i++)
		std::cin >> x_vals[i];
	
	for(int i=0; i<points_no; i++)
		std::cin >> y_vals[i];

	*_x_vals = x_vals;
	*_y_vals = y_vals;

	return points_no;
};

double evolution_cycle(Forest* forest, int threshold, double* x_vals, double* y_vals, int points_no, 
	int generation_no, double err, bool debug){

	//Performing the evolution cycle
	int i = 0;
	double E = err + 1.0;
	Tree* bestTree;
	std::chrono::duration<double> sel_time, mut_cross_time, newg_time, gen_time, overall_time;
	std::chrono::system_clock::time_point start, end, overall_start, overall_end;
    overall_start = std::chrono::system_clock::now();
    while(E >= err && ++i<=generation_no){
		std::vector<Tree*> newTrees;
		int* bestTrees;

		//Selection
    	start = std::chrono::system_clock::now();
        bestTrees = forest->selectBests(x_vals, y_vals, points_no, threshold);
    	end = std::chrono::system_clock::now();
		sel_time = end - start;

		//Mutation&Crossover
    	start = std::chrono::system_clock::now();
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
    	end = std::chrono::system_clock::now();
		mut_cross_time = end - start;

		//Replication
    	start = std::chrono::system_clock::now();
        forest->newGeneration(newTrees);
    	end = std::chrono::system_clock::now();
		newg_time = end - start;

		
		if(debug){
    		start = std::chrono::system_clock::now();
			bestTree = forest->getBestTree(x_vals, y_vals, points_no);
			E = forest->getBestFitness(x_vals, y_vals, points_no);
    		end = std::chrono::system_clock::now();
			sel_time += end - start;
			gen_time = sel_time + mut_cross_time + newg_time;

			std::cout << "Generation "<<i<<
			"\n\tSelection Time(s) = "<<sel_time.count()<<
			"\n\tMut&Cross Time(s) = "<<mut_cross_time.count()<<
			"\n\tNew gen   Time(s) = "<<newg_time.count()<<
			"\n\tWhole gen Time(s) = "<<gen_time.count()<<
			"\n\tBest Tree = "<< bestTree->toString()<<
			"\n\tFitness = "<<E<<
            "\n\n";
		}
    }
	overall_end = std::chrono::system_clock::now();
	overall_time = overall_end - overall_start;

    E = forest->getBestFitness(x_vals, y_vals, points_no);
	if(debug){
		if(i > generation_no) i--;
		bestTree = forest->getBestTree(x_vals, y_vals, points_no);
		std::cout <<
		"\nGENERATION "<<i<<
		"\nBEST TREE = "<<bestTree->toString()<<
		"\nFITNESS = "<<E<<
		"\nOVERALL TIME(s) = "<<overall_time.count()<<"\n";
	}
	return E;
};

double splitted_evolution_cycle(TestForest* test_forest, long tree_no, int depthmax, int randmax, int threshold, double* x_vals, double* y_vals, int points_no, 
	int generation_no, double err, int nw){
	std::vector<std::chrono::duration<double>> partition_times;

	int i = 0;
	Tree* bestTree;
	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<double> sel_time = std::chrono::system_clock::duration::zero();
    while(++i<=generation_no){
		std::vector<Tree*> newTrees;
		int* bestTrees;

		//Selection
		start = std::chrono::system_clock::now();
		for(int j=0; j<nw; j++)
			partition_times.push_back(test_forest->updatePoolFitness(x_vals, y_vals, points_no, j));
		test_forest->setFitnessUpdated();
        bestTrees = test_forest->selectBests(x_vals, y_vals, points_no, threshold);
		end = std::chrono::system_clock::now();
		sel_time = end - start;

		//Mutation&Crossover
        for(int j=0; j<threshold; j++){
			int r = std::rand()%3;
			if(r == 0) newTrees.push_back(test_forest->getTree(bestTrees[j])->copy());
			if(r == 1) newTrees.push_back(test_forest->mutation(bestTrees[j]));
			if(r == 2) {
				//Extraction without replacement
				int tree1_id, tree2_id;
				tree1_id = bestTrees[j];
				tree2_id = std::rand()%(threshold-1);
				if(tree2_id >= tree1_id) ++tree2_id;
				newTrees.push_back(test_forest->crossover(tree1_id, tree2_id));
			}
		}

		//Replication
        test_forest->newGeneration(newTrees);

		double E = test_forest->getBestFitness();

		for(int j=0; j<nw; j++){
			std::cout <<"results"<<
			" splitseq generation "<<i<<" sel_time(s) "<<sel_time.count()<<
			" partition "<<j<<" upfit_time(s) "<<partition_times[j].count()<<
			" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
			" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";
		}
		partition_times.clear();
    }

    return test_forest->getBestFitness(x_vals, y_vals, points_no);
};