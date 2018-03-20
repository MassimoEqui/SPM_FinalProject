#include <iostream>
#include <cstdlib>
#include <ctime>

#include "include/genetics/ParallelForest.h"
#include "src/main/evolution_cycle.hpp"

int main(int argc, char const *argv[])
{
	if(argc != 9){
		std::cout << "8 parameters needed and an input file to be specified\n"<<
			"Usage: ./parallel_main.out tree_no depthmax threshold randmax gen_no err nw debug  < input_f(x).txt\n"<<
			"example\n"<<
			"./parallel_main.out 12000 5 4000 10 25 0.5 8 no < input_cos(x)-pow(x,3)10-3.txt\n";
		return 0;
	}

	//Setting the rand() environment
	std::srand(std::time(nullptr));

	//Generating a new pool of functions (trees)
	long tree_no = std::atoi(argv[1]);
	int depthmax = std::atoi(argv[2]);
	int threshold = std::atoi(argv[3]);
	int randmax = std::atoi(argv[4]);
	int generation_no = std::atoi(argv[5]);
	double err = std::atof(argv[6]);
	int nw = std::atoi(argv[7]);
	bool debug = false;
	if(std::strcmp(argv[8],"yes")==0) debug = true; 

	ParallelForest* forest = new ParallelForest(tree_no, depthmax, randmax, nw);
	evolution_cycle(forest, tree_no, depthmax, threshold, randmax, generation_no, err, true, nw, debug);

	return 0;
}