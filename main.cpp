#include <iostream>
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
	
	clock_t begin = clock(); 
	int tsp = nearestNeighbor(graph, 0, tour);
	clock_t end = clock();

	std::cout << tsp << "\n";
	double time_secs = double(end - begin)/CLOCKS_PER_SEC;
	
	
	int tsp_tour = twoOpt(graphM, tour, tsp);
	std::cout << tsp_tour << "\n";

	std::vector<int> tsp_3opt = threeOpt(graphM, tour, tsp);
	
	/*
	for (auto &i : tsp_3opt) std::cout << i + 1 << " ";
	std::cout << "\n";
	*/
	
	std::cout << tourDistanceM(graphM, tsp_3opt) << "\n";

	return 0;
}  