#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

#include "src/main/evolution_cycle.hpp"

int main(int argc, char const *argv[])
{
	if(argc != 9){
		std::cout <<"8 parameters needed and an input file to be specified\n"<<
			"Usage: ./main.out tree_no depthmax threshold randmax randseed gen_no err debug < input_f(x).txt\n"<<
			"example\n"<<
			"./main.out 12000 5 4000 10 -1 20 0.5 no < \"input_cos(x)-pow(x,3)10-3.txt\"\n";	
		return 0;
	}

	//Generating a new pool of functions (trees)
	long tree_no = std::atoi(argv[1]);
	int depthmax = std::atoi(argv[2]);
	int threshold = std::atoi(argv[3]);
	int randmax = std::atoi(argv[4]);
	int randseed = std::atoi(argv[5]);
	int generation_no = std::atoi(argv[6]);
	double err = std::atof(argv[7]);
	bool debug = false;
	if(std::strcmp(argv[8],"yes")==0) debug = true; 

	//Setting the rand() environment
	randseed < 0 ? std::srand(std::time(nullptr)) : std::srand(randseed);
	
	std::chrono::duration<double> time;
	std::chrono::system_clock::time_point start, end;
	
    start = std::chrono::system_clock::now();
	double *x_vals, *y_vals;
	long points_no = read_input(&x_vals, &y_vals);
	Forest* forest = new Forest(tree_no, depthmax, randmax);
	double E = evolution_cycle(forest, threshold, x_vals, y_vals, points_no, generation_no, err, debug);
	end = std::chrono::system_clock::now();
	time = end - start;

	std::cout <<"results"<<
	" seq comptime(s) "<<time.count()<<" upfittime(s) "<<forest->getFitnessUpdateTime().count()<<
	" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
	" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";
	delete forest;
	return 0;
}