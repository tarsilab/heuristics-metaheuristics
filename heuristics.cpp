#include <limits>
#include <set>
#include <utility>
#include <iostream>
#include "heuristics.h"

int nearestNeighbor(Graph &g, int source, std::vector<int> &tour) {

	/*
		Nearest Neighbor.
		Starting from vertex one, we choose the nearest city that we haven't
		visited yet until we visit all of the vertices. Finally, we connect
		the last vertex with the first one.
	*/

	int original_source = source;
	int num_vertices = g.getNumVertices();
	int visited_vertices = 0;
	int new_source = 0;
	std::vector < std::vector < std::pair<int, int> > > adj_list = g.getAdjList();
	std::vector<bool> visited(num_vertices);

	visited_vertices = 1;
	int sum = 0;

	while (visited_vertices != num_vertices) {
		int smallest = std::numeric_limits<int>::max();
		visited[source] = true;
		tour.push_back(source);
		
		for (auto &i : adj_list[source]) {
			if (i.second < smallest && (visited[i.first] == false)) {
				smallest = i.second;
				new_source = i.first;
			}
		}

		if (source == new_source) {
			sum = 0;
			break;
		}
		
		sum += smallest;
		source = new_source;
		visited_vertices++;
	}  

	tour.push_back(source);

	if (sum != 0) {
		for (auto &i : adj_list[source]) if (i.first == original_source) sum += i.second;
	}

	return sum;
}

std::vector<int> twoOptSwap(std::vector<int> tour, int i, int k) {
	int tour_size = tour.size();
	std::vector<int> new_tour;

	for (int j = 0; j < i; ++j) new_tour.push_back(tour[j]);
	for (int j = k; j >= i; --j) new_tour.push_back(tour[j]); 
	for (int j = k+1; j < tour_size; ++j) new_tour.push_back(tour[j]);

	return new_tour;
}

int tourDistance(Graph &g, std::vector<int> &tour) {
	std::vector < std::vector < std::pair<int, int> > > adj_list = g.getAdjList();
	int distance = 0;
	
	for (int i = 0; i < tour.size() - 1; ++i) {
		for (auto &j : adj_list[tour[i] - 1]) {
			if (j.first == (tour[i+1] - 1)) distance += j.second;
		}
	}

	//std::cout << tour.back() << " " << tour.front() << "\n";
	for (auto &j : adj_list[tour.back() - 1]) {
		if (j.first == (tour.front() - 1)) distance += j.second;
	}

	return distance;
}

int twoOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int initial_d) {
	bool improvement = true;
	int tour_size = tour.size();
	int best_distance = initial_d;

	while(improvement) {
		improvement = false;

		for (int i = 1; i < tour_size - 1; ++i) {
			for (int j = i + 1; j < tour_size - 1; ++j) {
				std::vector<int> new_tour = twoOptSwap(tour, i, j);
				int new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[j+1]] + g[tour[i-1]][tour[j]] + g[tour[j+1]][tour[i]];
				
				if (new_distance < best_distance) {
					tour = new_tour;
					best_distance = new_distance;
					improvement = true;
					break;
				} 
			}
		}
	}

	return best_distance;
}

