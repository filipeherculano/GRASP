#include <iostream>

#include "grasp.h"

const std::string test_path[6] = {"instances/gr17.tsp", 
  "instances/gr24.tsp", 
  "instances/gr48.tsp", 
  "instances/si175.tsp", 
  "instances/si535.tsp", 
  "instances/si1032.tsp"};
const double initial_alpha = 0;
const int kMaxIter = 30;
const double runs = 100.0;

int main(){
  for(int j = 0; j < 6; ++j){
    double media = 0.0;
    for(int i = 0; i < (int) runs; ++i){
      Grasp controller(test_path[j], initial_alpha, kMaxIter);
      controller.run();
      media += controller.cmin();
    }
    printf("Media: %lf\n", media / runs);
  }
  return 0;
}
