#include <string>
#include <vector>

#include "graph.h"

class Grasp {
  public:
	const int inf = 0x3f3f3f3f;

	Grasp(const std::string test_path, double alpha, int kMaxIter) : 
	  test_path_(test_path), 
	  graph_(test_path), 
	  size_(graph_.size()), 
	  alpha_(alpha),
	  kMaxIter_(kMaxIter){
	  double cost = 0.0;
	  for(unsigned int u = 0; u < size_; ++u) {
		itinerary_.push_back(u);
		if(u) cost += graph_.distance(u-1, u);
		else cost += graph_.distance(u, size_-1);
	  }
	  cmax_ = cmin_ = cost;
	  printf("outside run : %d %lf\n", kMaxIter_, alpha_);
	  run();
	}

	void run();

	void show_results();

  private:
	bool is_candidate(double cost);

	void adapt_alpha();

	double swap_cost(unsigned int u);

	void swap_permutation(unsigned int u);

	std::string test_path_;
	Graph graph_;
	unsigned int size_;
	double alpha_;
	int kMaxIter_;
	double cmax_;
	double cmin_;
	std::vector<int> itinerary_;
};
