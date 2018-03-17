#include <iostream>
#include <cstdlib>
#include <ctime>

#include "include/genetics/ParallelForest.h"
#include "src/main/evolution_cycle.hpp"

int main(int argc, char const *argv[])
{
	if(argc != 8){
		std::cout << "7 parameters needed\n"<<
			"\t./parallel_main.out tree_no depthmax threshold randmax gen_no err nw;\n"<<
			"example\n"<<
			"\t./parallel_main.out 1000 5 400 10 50 0.5 4\n";	
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

	ParallelForest* forest = new ParallelForest(tree_no, depthmax, randmax, nw);
	evolution_cycle(forest, tree_no, depthmax, threshold, randmax, generation_no, err, true, nw);

	return 0;
}