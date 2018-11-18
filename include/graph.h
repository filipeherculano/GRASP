#include <iostream>
#include <string>
#include <vector>

class Graph {
  public:

    /*
     *	Default constructor.
     */
    Graph(const std::string test_path) : 
      current_node_(0), 
      current_neighbor_(0),
      ready_to_read_(false){
	parse_input_file(test_path);
      }

    /*
     *	Retrieves the distance between two different nodes in the graph.
     */
    double distance(int u, int v);

    /*
     *	Default get of class member 'size_'.
     */
    unsigned int size();

  private:

    /*
     *	Parses input file given an specific path file.
     */
    void parse_input_file(std::string test_path);

    /*
     *	Reads a specific section of the test file regarding
     * the edge distances. This matrix is triangular inferior.
     */
    void inferior_matrix_parse(std::string line);

    /*
     *	Reads a specific section of the test file regarding
     * the edge distances. This matrix is triangular superior.
     */
    void superior_matrix_parse(std::string line);

    int current_node_;				// Current node used on matrix build
    int current_neighbor_;			// Current neighbor node on matrix build
    bool ready_to_read_;			// Ready to read lines regarding distances
    unsigned int size_;				// Size of the graph
    std::vector< std::vector<double> > topo_; 	// Graph topology
};
