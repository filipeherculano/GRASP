#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Graph {
  public:
	Graph(const std::string test_path) : 
	  current_node_(0), 
	  current_neighboor_(0),
	  ready_to_read(false){
	  std::string line;
	  std::ifstream file;
	  file.open(test_path);
	  if(!file){
		std::cerr << "Error while opening file.\n";
		exit(1);
	  }

	  while(getline(file, line)) analyse_input(line);

	  file.close();
	}

	double distance(int u, int v);

	unsigned int size();

  private:
	void analyse_input(std::string line);

	int current_node_;
	int current_neighboor_;
	bool ready_to_read;
	unsigned int size_;
	std::vector< std::vector<double> > topo_; 
};
