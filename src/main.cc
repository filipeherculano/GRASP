#include <iostream>

#include "grasp.h"

const std::string test_path[6] = {"instances/gr17.tsp", 
			     "instances/gr24.tsp", 
			     "instances/gr48.tsp", 
			     "instances/si175.tsp", 
			     "instances/si535.tsp", 
			     "instances/si1032.tsp"};
const double initial_alpha = 1;
const int kMaxIter = 3000;

int main(){
	Grasp controller(test_path[0], initial_alpha, kMaxIter);
	controller.run();
	controller.show_results();
	return 0;
}
