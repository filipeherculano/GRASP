#include <iostream>
#include <string>
#include <vector>

class Graph {
  public:
	Graph(const std::string test_path) : 
	  current_node_(0), 
	  current_neighboor_(0),
	  ready_to_read_(false){
	  parse_input_file(test_path);
	}

	double distance(int u, int v);

	unsigned int size();

  private:
	void parse_input_file(std::string test_path);

	void inferior_matrix_parse(std::string line);
	
	void superior_matrix_parse(std::string line);

	int current_node_;
	int current_neighboor_;
	bool ready_to_read_;
	unsigned int size_;
	std::vector< std::vector<double> > topo_; 
};
