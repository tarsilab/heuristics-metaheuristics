#include <iostream>
#include <ctime>
#include "graph.h"
#include "heuristics.h"

int main(int argc, char *argv[]) {

	long long source, destination;
	int weight;
	int vertices;

	std::cin >> vertices;

	Graph graph(vertices);

	while (std::cin >> source >> destination >> weight) {
		graph.addEdge(source - 1, destination - 1, weight);
	}

	clock_t begin = clock(); 
	int tsp = nearestNeighbor(graph, 0);
	clock_t end = clock();

	double time_secs = double(end - begin)/CLOCKS_PER_SEC;
	std::cout << tsp << " " << time_secs << "\n";
	
	return 0;
}  