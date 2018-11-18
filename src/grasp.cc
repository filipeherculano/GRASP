#include "grasp.h"

#include <utility>

bool Grasp::test(double cost){
  double actual_cost = 0.0;
  for(int i = 0; i < (int) itinerary_.size(); ++i){
    actual_cost += graph_.distance(itinerary_[i], itinerary_[(i+1)%itinerary_.size()]);
  }
  return actual_cost == cost;
}

void Grasp::run(){
  std::vector< std::pair<unsigned int, double> > LRC;
  srand(time(NULL));
  while(kMaxIter_--){
    //std::cout << ">> "<< cmin_ << std::endl;
    for(unsigned int i = 0; i < size_; ++i){
      double cost = swap_cost(i);
      if(is_candidate(cost)) {
	LRC.push_back(std::make_pair(i, cost));
	//puts("PUSHED!");
      } //else puts("");
    }
    if(LRC.size() != 0){
      int random_choice = rand() % LRC.size();
      //printf("Random : %d %d\n", random_choice, LRC.size());
      swap_permutation(LRC[random_choice].first);
      if(!test(LRC[random_choice].second)) puts("WRONG!!\n");
      current_ = LRC[random_choice].second;
      cmin_ = std::min(cmin_ , current_);
      cmax_ = std::max(cmax_ , current_);
    }

    LRC.clear();
    adapt_alpha();
  }
}

void Grasp::show_results(){
  std::cout << "Result of test " << test_path_ << " is : " << cmin_ << std::endl;
}

bool Grasp::is_candidate(double cost){
  return cost < (cmin_ + (alpha_ * (cmax_ - cmin_)));
}

void Grasp::adapt_alpha(){

}

double Grasp::swap_cost(unsigned int i){
  unsigned int u = itinerary_[i];
  unsigned int prev_node = itinerary_[(i-1+size_) % size_];
  unsigned int v = itinerary_[(i+1) % size_];
  unsigned int next_node = itinerary_[(i+2) % size_];

  double cost = current_;
  auto a = graph_.distance(prev_node, u);
  auto b = graph_.distance(v, next_node);
  auto c = graph_.distance(prev_node, v);
  auto d = graph_.distance(u, next_node);
  cost -= a;
  cost -= b;
  cost += c;
  cost += d;
  //printf("(%d,%d,%d,%d)%.0lf - %.0lf - %.0lf + %.0lf + %.0lf = %.0lf ",prev_node,u,v,next_node, current_, a,b,c,d,cost);

  return cost;
}

void Grasp::swap_permutation(unsigned int i){
  std::swap(itinerary_[i], itinerary_[(i+1) % size_]);
}
