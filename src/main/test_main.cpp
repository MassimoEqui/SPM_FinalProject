#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>

#include "include/genetics/TestForest.h"
#include "include/genetics/FF_Forest.h"
#include "src/main/evolution_cycle.hpp"

int main(int argc, char const *argv[])
{
	if(argc != 8){
		std::cout << "7 parameters needed and an input file to be specified\n"<<
			"Usage: ./test_main.out tree_no depthmax threshold randmax gen_no err nw < input_f(x).txt\n"<<
			"example\n"<<
			"./test_main.out 12000 5 4000 10 20 0.5 8 < \"input_cos(x)-pow(x,3)10-3.txt\"\n";
		return 0;
	}

	//Setting the rand() environment
	std::srand(std::time(nullptr));

	//Setting the parameters
	long tree_no = std::atoi(argv[1]);
	int depthmax = std::atoi(argv[2]);
	int threshold = std::atoi(argv[3]);
	int randmax = std::atoi(argv[4]);
	int generation_no = std::atoi(argv[5]);
	double err = std::atof(argv[6]);
	int nw = std::atoi(argv[7]);

	//Generating a new pool of functions (trees) to be reused
	TestForest* test_forest = new TestForest(tree_no, depthmax, randmax, nw);
	std::pair<Tree*, double>* treePool = test_forest->getTreePool();

	std::chrono::duration<double> time;
	std::chrono::system_clock::time_point start, end;
	std::vector<std::chrono::duration<double>> partition_times;

	/******************** SPLITTED SEQUENTIAL EXECUTION ********************/

	double *x_vals, *y_vals;
	long points_no = read_input(&x_vals, &y_vals);

	double E;
    start = std::chrono::system_clock::now();
	E = splitted_evolution_cycle(test_forest, threshold, x_vals, y_vals, points_no, generation_no, err, nw);
	end = std::chrono::system_clock::now();
	time = end - start;

	std::cout <<"results"<<
	" splitseq nw "<<nw<<" comptime(s) "<<time.count()<<" upfittime(s) "<<test_forest->getFitnessUpdateTime().count()<<
	" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
	" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";

	delete test_forest;

	/******************** STANDARD SEQUENTIAL EXECUTION ********************/
	
	for(int i=0; i<7; i++){
		Forest* forest = new Forest(treePool, tree_no, depthmax, randmax);
		start = std::chrono::system_clock::now();
		E = evolution_cycle(forest, threshold, x_vals, y_vals, points_no, generation_no, err, false);
		end = std::chrono::system_clock::now();
		time = end - start;

		std::cout <<"results"<<
		" seq comptime(s) "<<time.count()<<" upfittime(s) "<<forest->getFitnessUpdateTime().count()<<
		" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
		" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";
		delete forest;
	}

	/******************** FASTFLOW EXECUTION ********************/

	for(int i=0; i<7; i++){
		FF_Forest* ff_forest = new FF_Forest(treePool, tree_no, depthmax, randmax, nw);
		start = std::chrono::system_clock::now();
		E = evolution_cycle(ff_forest, threshold, x_vals, y_vals, points_no, generation_no, err, false);
		end = std::chrono::system_clock::now();
		time = end - start;

		std::cout <<"results"<<
		" ff nw "<<nw<<
		" comptime(s) "<<time.count()<<" upfittime(s) "<<ff_forest->getFitnessUpdateTime().count()<<
		" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
		" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";
		delete ff_forest;
	}

	return 0;
}