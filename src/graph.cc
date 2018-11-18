#include <fstream>
#include <sstream>

#include "graph.h"

double Graph::distance(int u, int v){ return topo_[u][v]; }

unsigned int Graph::size(){ return size_; }

void Graph::parse_input_file(std::string test_path){
  std::string line;
  std::ifstream file;
  file.open(test_path);
  if(!file){
    std::cerr << "Error while opening file.\n";
    exit(1);
  }

  getline(file, line);
  if(line[6] == 'g')
    while(getline(file, line)) inferior_matrix_parse(line);
  else 
    while(getline(file, line)) superior_matrix_parse(line);

  file.close();
}

void Graph::inferior_matrix_parse(std::string line){
  std::string word;
  std::vector<std::string> words;
  std::stringstream ss(line);

  while(ss >> word) words.push_back(word);

  if(ready_to_read_){
    if(words[0] == "EOF") ready_to_read_ = false;
    else {
      for(int i = 0; i < (int) words.size(); ++i){
	double weight = (double) std::stoi(words[i]);
	if(weight == 0) ++current_node_, current_neighbor_ = 0;
	else {
	  topo_[current_node_][current_neighbor_] = weight;
	  topo_[current_neighbor_][current_node_] = weight;
	  ++current_neighbor_;
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
    if(words[0] == "EDGE_WEIGHT_SECTION") ready_to_read_ = true;
  }
}

void Graph::superior_matrix_parse(std::string line){
  std::string word;
  std::vector<std::string> words;
  std::stringstream ss(line);

  while(ss >> word) words.push_back(word);

  if(ready_to_read_){
    if(words[0] == "EOF") ready_to_read_ = false;
    else {
      for(int i = 0; i < (int) words.size(); ++i){
	double weight = (double) std::stoi(words[i]);
	topo_[current_node_][current_neighbor_] = weight;
	topo_[current_neighbor_][current_node_] = weight;
	++current_neighbor_;
	if(current_neighbor_ == (int) size_) current_neighbor_ = ++current_node_;
      }
    }
  } else {
    if(words[0] == "DIMENSION:"){
      size_ = std::stoi(words[1]);
      std::vector<double> temp(size_);
      for(unsigned int i = 0; i < size_; ++i)
	topo_.push_back(temp);
    }
    if(words[0] == "EDGE_WEIGHT_SECTION") ready_to_read_ = true;
  }
}
