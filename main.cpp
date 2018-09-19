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

	//printGraphM(graphM, vertices);

	std::vector<int> tour;
	
	clock_t begin = clock(); 
	int tsp = nearestNeighbor(graph, 0, tour);
	clock_t end = clock();

	double time_secs = double(end - begin)/CLOCKS_PER_SEC;
	//std::cout << tsp << "\n";
	//graph.printGraph();

	for (auto & i : tour) std::cout << i + 1<< " ";
	std::cout << "\n";	
	
	/*
	std::vector<int> new_tour = twoOptSwap(tour, 2, 5);
	for (auto & i : new_tour) std::cout << i << " ";
	std::cout << "\n";
	*/

	int tsp_tour = twoOpt(graphM, tour, tsp);
	std::cout << tsp_tour << "\n";

	//int distance = tourDistance(graph, tour);
	//std::cout << distance << "\n";
	
	return 0;
}  