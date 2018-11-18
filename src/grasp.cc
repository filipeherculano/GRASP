#include "grasp.h"

#include <utility>

void Grasp::run(){
	std::vector< std::pair<unsigned int, double> > LRC;
	printf("inside run : %d %lf\n", kMaxIter_, alpha_);
	std::cout << test_path_ << std::endl;
	/*while(kMaxIter_--){
		for(unsigned int u = 0; u < size_; ++u){
			double cost = swap_cost(u);
			if(is_candidate(cost)) 
				LRC.push_back(std::make_pair(u, cost));
		}
		if(LRC.size() != 0){
			srand(time(0));
			int random_choice = rand() % LRC.size();
			swap_permutation(LRC[random_choice].first);
			cmin_ = std::min(cmin_ , LRC[random_choice].second);
			cmax_ = std::max(cmax_ , LRC[random_choice].second);
		}

		LRC.clear();
		adapt_alpha();
		printf("%d\n", kMaxIter_);
	}*/
}

void Grasp::show_results(){
	std::cout << "Result of test " << test_path_ << " is : " << cmin_ << std::endl;
}

bool Grasp::is_candidate(double cost){
	return cost <= (cmin_ + (alpha_ * (cmax_ - cmin_)));
}

void Grasp::adapt_alpha(){

}

double Grasp::swap_cost(unsigned int u){
	unsigned int v = (u == size_-1 ? 0:u+1);
	unsigned int prev_node = (u ? u-1:size_-1);
	unsigned int next_node = (v == size_-1 ? 0:v+1);

	double cost = cmin_;
	cost -= graph_.distance(prev_node, u);
	cost -= graph_.distance(v, next_node);
	cost += graph_.distance(prev_node, v);
	cost += graph_.distance(u, next_node);

	return cost;
}

void Grasp::swap_permutation(unsigned int u){
	if(u == size_-1) std::swap(itinerary_[u], itinerary_[0]);
	else std::swap(itinerary_[u], itinerary_[u+1]);
}
