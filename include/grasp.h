#include <string>
#include <vector>

#include "graph.h"

class Grasp {
  public:

    /*
     *	Default constructor.
     */
    Grasp(const std::string test_path, double alpha, int kMaxIter) : 
      test_path_(test_path), 
      graph_(test_path), 
      size_(graph_.size()), 
      alpha_(alpha),
      kMaxIter_(kMaxIter){
	construct_initial_solution();
      }

    /*
     *	Runs Metaheuristic GRASP to solve TSP.
     */
    void run();

    /*
     *	Prints result.
     */
    void show_results();

    /*
     *	Default get of class member 'cmin_'.
     */
    double cmin(){ return cmin_; }

    /*
     *	Default get of class member 'initial_'.
     */
    double initial(){ return initial_; }

  private:

    /*
     *	Construct initial solution for TSP.
     */
    void construct_initial_solution();

    /*
     *	Checks whether the neighbor states are valid candidates
     * to be chosen.
     */
    bool is_candidate(double cost);

    /*
     *	Changes the current number of alpha based on a adaptive algorithm.
     */
    void adapt_alpha();

    /*
     *	Computes the cost of the neighbor state.
     */
    double swap_cost(unsigned int i, unsigned j);

    /*
     *	Swaps the current permutation, changing the current state.
     */
    void swap_permutation(unsigned int u, unsigned int v);

	double cost_of_linking(unsigned int i);

    std::string test_path_;		// Test file path
    Graph graph_;			// Graph representation
    unsigned int size_;			// Graph size
    double alpha_;			// Alpha value, between [0,1]
    int kMaxIter_;			// Maximum number of iterations of GRASP
    double cmax_;			// Maximum cost found
    double cmin_;			// Minimum cost found
    double current_;			// Current cost
    double initial_;			// Initial solution
    std::vector<int> itinerary_;	// Current itinerary of Traveling Salesman
};
