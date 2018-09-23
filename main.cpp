#include <ctime>
#include "graph.h"
#include "heuristics.h"

void printGraphM(std::vector< std::vector<int> > &g, int v) {
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j < v; ++j) {
			std::cout << g[i][j] << " ";
		}
		std::cout << "\n";
	}
}

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
	vnd(graphM, tour, tsp);
	std::cout << tsp << "\n";
	
	return 0;
}  