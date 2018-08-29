#include <iostream>
#include <cstring>
#include <limits>
#include "graph.h"

int nearestNeighbor(Graph &g, int source) {
	int original_source = source;
	int numVertices = g.getNumVertices();
	int visitedVertices = 0;
	int newSource = 0;
	std::vector < std::vector < std::pair<int, int> > > adjList = g.getAdjList();
	std::vector<bool> visited(numVertices);

	visitedVertices = 1;
	int sum = 0;

	while (visitedVertices != numVertices) {
		int smallest = std::numeric_limits<int>::max();
		visited[source] = true;
		
		for (auto &i : adjList[source]) {
			if (i.second < smallest && (visited[i.first] == false)) {
				smallest = i.second;
				newSource = i.first;
			}
		}

		if (source == newSource) {
			sum = 0;
			break;
		}
		
		sum += smallest;
		source = newSource;
		visitedVertices++;
	}  

	if (sum != 0) {
		for (auto &i : adjList[source])	if (i.first == original_source) sum += i.second;
	}

	return sum;
}

int main(int argc, char *argv[]) {

	long long source, destination;
	int weight;
	int vertices;

	std::cin >> vertices;

	Graph graph(vertices);

	while (std::cin >> source >> destination >> weight) {
		graph.addEdge(source - 1, destination - 1, weight);
	}

	int tsp = nearestNeighbor(graph, 0) ;
	std::cout << tsp << "\n";
	//graph.printGraph();
	
	return 0;
}  