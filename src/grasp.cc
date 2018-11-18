void Grasp::run(){
	std::vector< pair<int, double> > LRC;
	while(kMaxIter){
		for(unsigned int u = 0; u < size_; ++u){
			double cost = swap_cost(u);
			if(is_candidate(cost)) 
				LRC.push_back(make_pair(u, cost));
		}
		if(LRC.size() != 0){
			srand(time(0));
			int random_choice = rand() % LRC.size();
			swap_permutation(LRC[random_choice].first);
			cmin_ = min(cmin_ , LRC[random_choice].second);
			cmax_ = max(cmax_ , LRC[random_choice].second);
		}

		LRC.clear();
		--kMaxIter;
		adapt_alpha();
	}
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

}

double Grasp::swap_permutation(unsigned int u){
	if(u == size_-1) swap(itinerary_[u], itinerary_[0]);
	else swap(itinerary_[u], itinerary_[u+1]);
}
