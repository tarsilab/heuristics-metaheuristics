#include <ctime>
#include "graph.h"
#include "heuristics.h"

/*
	Compile (use Makefile!):
		make

	Run:
		./tp1 < input
*/

int main(int argc, char *argv[]) {

	long long source, destination;
	int weight;
	int vertices;

	std::cin >> vertices;

	Graph graph(vertices);

	std::vector< std::vector<int> > graphM(vertices, std::vector<int>(vertices, 0));

	while (std::cin >> source >> destination >> weight) {
		graph.addEdge(source - 1, destination - 1, weight);
		graphM[source - 1][destination - 1] = weight;
		graphM[destination - 1][source - 1] = weight;
	}

	std::vector<int> tour;

	int tsp = nearestNeighbor(graph, 0, tour);
	//vnd(graphM, tour, tsp);
	tabuSearch(graphM, vertices, tour, tsp);
	std::cout << tsp << "\n";

	return 0;
}  