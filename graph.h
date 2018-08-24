#include <vector>
#include <utility>

#ifndef GRAPH_H
#define GRAPH_H

class Graph {

	int num_vertices;
	int num_edges;
	std::vector < std::vector< std::pair<int, int> > > adj_list;

	public:
		Graph(int v);
		~Graph();
		void addEdge(int s, int d, int w);
		void printGraph();	
		std::vector < std::vector< std::pair<int, int> > > getAdjList();
		long long getNumVertices();
		long long getNumEdges();
};

#endif