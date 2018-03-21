#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

#include "src/main/evolution_cycle.hpp"

int main(int argc, char const *argv[])
{
	if(argc != 8){
		std::cout <<"7 parameters needed and an input file to be specified\n"<<
			"Usage: ./main.out tree_no depthmax threshold randmax gen_no err debug < input_f(x).txt\n"<<
			"example\n"<<
			"./main.out 12000 5 4000 10 20 0.5 no < input_cos(x)-pow(x,3)10-3.txt\n";	
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
	bool debug = false;
	if(std::strcmp(argv[7],"yes")==0) debug = true; 

	Forest* forest = new Forest(tree_no, depthmax, randmax);
	evolution_cycle(forest, tree_no, depthmax, threshold, randmax, generation_no, err, false, 1, debug);

	return 0;
}