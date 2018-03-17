#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<vector>

#include "include/genetics/Forest.h"

#define DEPTHMAX 8
#define TREE_NO 1000
#define MAXRANDNUM 10
#define RANGE_SIZE 100

int main(int argc, char* const argv[]){
    std::srand(std::time(nullptr));
    
    Forest* forest = new Forest(0,0,0);
    Tree* tree;

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

    std::cout <<"DEPTH, Evaluate Time(microseconds), Fitness Time(microseconds)\n";
    for(int i=1; i<=DEPTHMAX; i++){
        std::chrono::duration<double, std::micro> duration_sum_evaluate;
        std::chrono::duration<double, std::micro> duration_sum_fitness;
        std::chrono::steady_clock::time_point start, end;
        duration_sum_evaluate = start - start;
        duration_sum_fitness = start - start;
        for(int j=0; j<TREE_NO; j++){
            tree = new Tree(i, MAXRANDNUM);
            double r = ((double)std::rand()/(double)RAND_MAX)*(double)RANGE_SIZE;
            start = std::chrono::steady_clock::now();
            tree->evaluate(r);
            end = std::chrono::steady_clock::now();
            duration_sum_evaluate += end - start;

            start = std::chrono::steady_clock::now();
            forest->fitness(tree, x_vals, y_vals, points_no);
            end = std::chrono::steady_clock::now();
            duration_sum_fitness += end - start;
        }
        std::cout<<i<<
            ", "<<duration_sum_evaluate.count()/(double)TREE_NO<<
            ", "<<duration_sum_fitness.count()/(double)TREE_NO<<"\n";
    }

    return 0;
}