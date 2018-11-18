#include <string>
#include <vector>

#include "graph.h"

class Grasp {
  public:
    Grasp(const std::string test_path, double alpha, int kMaxIter) : 
      test_path_(test_path), 
      graph_(test_path), 
      size_(graph_.size()), 
      alpha_(alpha),
      kMaxIter_(kMaxIter){
	double cost = 0.0;
	for(unsigned int u = 0; u < size_; ++u) {
	  itinerary_.push_back(u);
	  cost += graph_.distance(u, (u+1)%size_);
	}
	current_ = cmax_ = cmin_ = cost;
      }

    void run();

    void show_results();

    double cmin(){ return cmin_; }

  private:
    bool test(double cost);

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
    double current_;
    std::vector<int> itinerary_;
};
