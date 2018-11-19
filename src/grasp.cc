#include <algorithm>
#include <cstring>
#include <utility>

#include "grasp.h"

void Grasp::run(){
	std::vector< std::pair<double, std::pair<unsigned int, unsigned int> > > LRC;
	srand(time(NULL));
	while(kMaxIter_--){
		for(unsigned int i = 0; i < size_; ++i){
			for(unsigned int j = i+1; j < size_; ++j){
				double cost = swap_cost(i,j);
				if(is_candidate(cost)) LRC.push_back(std::make_pair(cost, std::make_pair(i,j)));
			}
		}

		if(LRC.size() != 0){
			sort(LRC.begin(), LRC.end());
			while(LRC.size() > 20) LRC.pop_back();
			int random_choice = rand() % LRC.size();
			swap_permutation(LRC[random_choice].second.first, LRC[random_choice].second.second);
			current_ = LRC[random_choice].first;
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

double Grasp::swap_cost(unsigned int i, unsigned int j){
	// Temporary slow POC
	double cost = current_ - cost_of_linking(i) - cost_of_linking(j);
	std::swap(itinerary_[i], itinerary_[j]);
	cost += cost_of_linking(i) + cost_of_linking(j);
	std::swap(itinerary_[i], itinerary_[j]);

	return cost;
}

void Grasp::swap_permutation(unsigned int u, unsigned int v){
	std::swap(itinerary_[u], itinerary_[v]);
}

double Grasp::cost_of_linking(unsigned int i){
	double u = itinerary_[i];
	double _prev = itinerary_[(i-1+size_) % size_];
	double _next = itinerary_[(i+1) % size_];

	return graph_.distance(_prev, u) + graph_.distance(u, _next);   
}
