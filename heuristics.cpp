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

int tourDistanceM(std::vector< std::vector<int> > &g, std::vector<int> tour) {
	int distance = 0;
	int tour_size = tour.size();
	for (int i = 0; i < tour_size - 1; ++i) {
		distance += g[tour[i]][tour[i+1]];
	}

	distance += g[tour[0]][tour[tour_size - 1]];

	return distance;
}

int twoOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int initial_d) {
	bool improvement = true;
	int tour_size = tour.size();
	int best_distance = initial_d;
	std::vector<int> original_tour = tour;

	std::cout << tourDistanceM(g, tour) << "\n"; 
	while(improvement) {
		improvement = false;

		for (int i = 1; i < tour_size - 1; ++i) {
			for (int j = i + 1; j < tour_size; ++j) {

				std::vector<int> new_tour = twoOptSwap(tour, i, j);
				
				// It doesn't make the last trade: the last with the one before cause of bounds
				int new_distance = 0;
				if (j == tour_size - 1) new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[0]] + g[tour[i-1]][tour[j]] + g[tour[0]][tour[i]];
				else new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[j+1]] + g[tour[i-1]][tour[j]] + g[tour[j+1]][tour[i]];
				
				if (new_distance < best_distance) {
					tour = new_tour;
					best_distance = new_distance;
					improvement = true;
				} 
			}
		}
	}
	
	return best_distance;
}

std::vector<int> threeOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int initial_d) {
	bool improvement = true;
	int tour_size = tour.size();
	int delta = 0;
	std::vector<int> new_tour(tour_size);

	for (int i = 1; i < tour_size - 3; ++i) {
		for (int j = i + 1; j < tour_size - 2; ++j) {
			for (int k = j + 1; k < tour_size - 1; ++k) {
				int delta = threeOptSwap(g, tour, new_tour, i, j, k);
			}
		}
	}

	if (delta < 0) {
		tour = new_tour;
		return threeOpt(g, tour, initial_d);
	}

	return new_tour;
}

int threeOptSwap(std::vector< std::vector<int> > &g, std::vector<int> &tour, std::vector<int> &new_tour, int i, int j, int k) {
	int tour_size = tour.size();
	int d0 = g[tour[i-1]][tour[i]] + g[tour[j-1]][tour[j]] + g[tour[k-1]][tour[k % tour_size]];
	int d1 = g[tour[i-1]][tour[j-1]] + g[tour[i]][tour[j]] + g[tour[k-1]][tour[k % tour_size]];
	int d2 = g[tour[i-1]][tour[i]] + g[tour[j-1]][tour[k-1]] + g[tour[j]][tour[k % tour_size]];
	int d3 = g[tour[i-1]][tour[j]] + g[tour[i]][tour[k-1]] + g[tour[j-1]][tour[k % tour_size]];
	int d4 = g[tour[k % tour_size]][tour[i]] + g[tour[j-1]][tour[j]] + g[tour[k-1]][tour[i-1]];
	
	if (d0 > d1) {
		int m = 0;

		for (int l = 0; l < i; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}
		
		for (int l = i; l >= j; --l) {
			new_tour[m] = (tour[l]);
			m++;
		}
		
		for (int l = j + 1; l < tour_size; ++l)  {
			new_tour[m] = (tour[l]); 
			m++;
		}
		return -d0 + d1;
	}

	else if (d0 > d2) {
		int m = 0;
		
		for (int l = 0; l < j; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}
		
		for (int l = j; l >= k; --l) {
			new_tour[m] = (tour[l]);
			m++;
		}
		
		for (int l = k + 1; l < tour_size; ++l) {
			new_tour[m] = (tour[l]); 
			m++;
		}
		
		return -d0 + d2;	
	}

	else if (d0 > d4) {
		int m = 0;

		for (int l = 0; l < i; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}

		for (int l = i; l >= k; --l) {
			new_tour[m] = (tour[l]);
			m++;
		}

		for (int l = k + 1; l < tour_size; ++l) {
			new_tour[m] = (tour[l]); 
			m++;
		}

		return -d0 + d4;	
	}	

	else if (d0 > d3) {
		int m = 0;

		for (int l = 0; l < i; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}

		for (int l = j; l <= k; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}

		for (int l = i; l < j; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}

		for (int l = k + 1; l < tour_size; ++l) {
			new_tour[m] = (tour[l]);
			m++;
		}
		
		return -d0 + d3;
	}	

	return d0;
	
}
