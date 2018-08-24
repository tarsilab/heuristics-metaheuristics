#include <iostream>
#include <cstring>
#include "graph.h"

int main(int argc, char *argv[]) {

	long long source, destination;
	float weight;
	int vertices;

	std::cin >> vertices;

	Graph graph(vertices);

	while (std::cin >> source >> destination >> weight) {
		graph.addEdge(source - 1, destination - 1, weight);
	}

	//graph.printGraph();
	
	return 0;
}  