#include <iostream>

#include "grasp.h"

const string test_path[6] = {"~/GRASP/instances/gr17.tsp", 
			     "~/GRASP/instances/gr24.tsp", 
			     "~/GRASP/instances/gr48.tsp", 
			     "~/GRASP/instances/si175.tsp", 
			     "~/GRASP/instances/si535.tsp", 
			     "~/GRASP/instances/si1032.tsp"};

int main(){
	Grasp controller(test_path[0]);
	controller.run();
	controller.show_results();
	return 0;
}
