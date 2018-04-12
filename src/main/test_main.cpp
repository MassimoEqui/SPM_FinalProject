#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>

#include "include/genetics/TestForest.h"

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

	//Generating a new pool of functions (trees)
	long tree_no = std::atoi(argv[1]);
	int depthmax = std::atoi(argv[2]);
	int threshold = std::atoi(argv[3]);
	int randmax = std::atoi(argv[4]);
	int generation_no = std::atoi(argv[5]);
	double err = std::atof(argv[6]);
	int nw = std::atoi(argv[7]);

	std::chrono::duration<double> time;
	std::chrono::system_clock::time_point start, end;
	TestForest* forest = new TestForest(tree_no, depthmax, randmax, nw);

	std::vector<std::chrono::duration<double>> partition_times;

    start = std::chrono::system_clock::now();

	//Evolution Cycle

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
	std::chrono::system_clock::time_point upfit_start, upfit_end;
	std::chrono::duration<double> upfit_time = std::chrono::system_clock::duration::zero();
    while(E >= err && ++i<=generation_no){
		std::vector<Tree*> newTrees;
		int* bestTrees;

		//Selection
		upfit_start = std::chrono::system_clock::now();

		for(int j=0; j<nw; j++)
			partition_times.push_back(forest->updatePoolFitness(x_vals, y_vals, points_no, j));
		forest->setFitnessUpdated();

		upfit_end = std::chrono::system_clock::now();
		upfit_time = upfit_end - upfit_start,
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

		//Replication
        forest->newGeneration(newTrees);

		std::cout << "\nGENERATION "<<i<<"\n"<<
		"sel_time: "<<upfit_time.count()<<"\n";
		for(int j=0; j<nw; j++)
			std::cout << "partition "<<j<<" time(s) = " << partition_times[j].count() << "\n";
		partition_times.clear();
    }

    E = forest->getBestFitness(x_vals, y_vals, points_no);
	
	end = std::chrono::system_clock::now();
	time = end - start;

	std::cout <<"results"<<
	" seq comptime(s) "<<time.count()<<" upfittime(s) "<<forest->getFitnessUpdateTime().count()<<
	" tree_no "<<tree_no<<" depthmax "<<depthmax<<" threshold "<<threshold<<
	" randmax "<<randmax<<" gen_no "<<generation_no<<" err "<<err<<" fitness "<<E<<"\n";
	delete forest;
	return 0;
}