#include <chrono>
#include <iostream>

#include "grasp.h"

const std::string test_path[6] = {"instances/gr17.tsp", 
  "instances/gr24.tsp", 
  "instances/gr48.tsp", 
  "instances/si175.tsp", 
  "instances/si535.tsp", 
  "instances/si1032.tsp"};
const double best_solution[6] = {2085, 1272, 5046, 21407, 48450, 92650};
const double initial_alpha = 0.85;
const int kMaxIter = 30;

int main(){
  for(int j = 0; j < 6; ++j){
    puts("-------------------------------------------------------------");
    std::cout << "Testing: " << test_path[j] << std::endl;
    printf("Initial alpha value: %lf\n", initial_alpha);
    printf("Maximum number of iterations of GRASP algorithm: %d\n\n", kMaxIter);

    Grasp controller(test_path[j], initial_alpha, kMaxIter);
    auto start = std::chrono::high_resolution_clock::now();
    controller.run();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    printf("Initial media: %lf\n", controller.initial());
    printf("Minimum found: %lf\n", controller.cmin());
    printf("This solution is %.2lf%% different from best solution.\n", ((controller.cmin()-best_solution[j])/best_solution[j])*100.0);
    std::cout << "Time spent: " << duration.count()/1000.0 << " ms" << std::endl;
    puts("-------------------------------------------------------------\n");
  }
  return 0;
}
