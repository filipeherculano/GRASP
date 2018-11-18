class Graph {
  public:
	Graph(const string test_path) {}

	double distance(int u, int v);

	unsigned int size();

  private:
	unsigned int size_;
	std::vector< std::vector<double> > topo_; 
};
