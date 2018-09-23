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

	int original_distance = tsp;
	std::vector<int> original_tour = tour;
		
	runTwoOpt(graphM, tour, tsp);
	std::cout << tsp << "\n";
	
	runThreeOpt(graphM, original_tour, original_distance);
	std::cout << original_distance << "\n";

	return 0;
}  