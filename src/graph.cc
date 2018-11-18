#include <sstream>

#include "graph.h"

double Graph::distance(int u, int v){ return topo_[u][v]; }

unsigned int Graph::size(){ return size_; }

void Graph::analyse_input(std::string line){
  std::string word;
  std::vector<std::string> words;
  std::stringstream ss(line);

  while(ss >> word) words.push_back(word);

  if(ready_to_read){
    if(words[0] == "EOF") ready_to_read = false;
    else {
      for(int i = 0; i < (int) words.size(); ++i){
	double weight = (double) std::stoi(words[i]);
	if(weight == 0) ++current_node_, current_neighboor_ = 0;
	else {
	  topo_[current_node_][current_neighboor_] = weight;
	  topo_[current_neighboor_][current_node_] = weight;
	  ++current_neighboor_;
	}
      }
    }
  } else {
    if(words[0] == "DIMENSION:"){
      size_ = std::stoi(words[1]);
      std::vector<double> temp(size_);
      for(unsigned int i = 0; i < size_; ++i)
	topo_.push_back(temp);
    }
    if(words[0] == "EDGE_WEIGHT_SECTION") ready_to_read = true;
  }
}
