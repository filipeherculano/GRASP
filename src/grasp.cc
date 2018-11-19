#include <cstring>
#include <utility>

#include "grasp.h"

void Grasp::run(){
  std::vector< std::pair<unsigned int, double> > LRC;
  srand(time(NULL));
  while(kMaxIter_--){
    for(unsigned int i = 0; i < size_; ++i){
      double cost = swap_cost(i);
      if(is_candidate(cost)) LRC.push_back(std::make_pair(i, cost));
    }
    if(LRC.size() != 0){
      int random_choice = rand() % LRC.size();
      swap_permutation(LRC[random_choice].first);
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

void Grasp::construct_initial_solution(){
  double cost = 0.0;
  bool state[size_];
  int u = 0, nxt;
  memset(state, false, sizeof state);

  while(itinerary_.size() != size_){
    int smallest = 0x3f3f3f3f; // Start with infinite value
    itinerary_.push_back(u);
    state[u] = true; // visiting

    for(int v = 0; v < (int) size_; ++v) {
      int weight = graph_.distance(u,v);
      if(!state[v] && smallest > weight){
	smallest = weight;
	nxt = v;
      }
    }

    if(smallest != 0x3f3f3f3f){
      cost += smallest;
      u = nxt;
    } else cost += graph_.distance(itinerary_[0], itinerary_.back());
  }

  initial_ = current_ = cmax_ = cmin_ = cost;
}

bool Grasp::is_candidate(double cost){
  return cost <= (cmin_ + (alpha_ * (cmax_ - cmin_)));
}

void Grasp::adapt_alpha(){
  // TODO (filipe.herculano) : Implement changing function of alpha
}

double Grasp::swap_cost(unsigned int i){
  unsigned int u = itinerary_[i];
  unsigned int prev_node = itinerary_[(i-1+size_) % size_];
  unsigned int v = itinerary_[(i+1) % size_];
  unsigned int next_node = itinerary_[(i+2) % size_];

  double cost = current_;
  cost -= graph_.distance(prev_node, u);
  cost -= graph_.distance(v, next_node);
  cost += graph_.distance(prev_node, v);
  cost += graph_.distance(u, next_node);

  return cost;
}

void Grasp::swap_permutation(unsigned int i){
  std::swap(itinerary_[i], itinerary_[(i+1) % size_]);
}
