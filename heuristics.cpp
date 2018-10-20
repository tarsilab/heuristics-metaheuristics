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

	/*
		Makes the only possible change to two edges. 
	*/

	int tour_size = tour.size();
	std::vector<int> new_tour;

	for (int j = 0; j < i; ++j) new_tour.push_back(tour[j]);
	for (int j = k; j >= i; --j) new_tour.push_back(tour[j]); 
	for (int j = k+1; j < tour_size; ++j) new_tour.push_back(tour[j]);

	return new_tour;
}

bool twoOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int &best_distance) {
	int tour_size = tour.size();
	
	/*
		Calls twoOptSwap for every combination of two edges of the graph.
	*/

	for (int i = 1; i < tour_size - 1; ++i) {
		for (int j = i + 1; j < tour_size; ++j) {

			std::vector<int> new_tour = twoOptSwap(tour, i, j);
			
			int new_distance = 0;
			if (j == tour_size - 1) new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[0]] + g[tour[i-1]][tour[j]] + g[tour[0]][tour[i]];
			else new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[j+1]] + g[tour[i-1]][tour[j]] + g[tour[j+1]][tour[i]];
				
			if (new_distance < best_distance) {
				tour = new_tour;
				best_distance = new_distance;
				return true;
			} 
		}
	}
	return false;
}

bool threeOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int &best_distance) {

	/*
		Calls threeOptSwap for every combination of three edges of the graph.
	*/

	int tour_size = tour.size();
	
	for (int i = 1; i < tour_size - 2; ++i) {
		for (int j = i + 1; j < tour_size - 1; ++j) {
			for (int k = j + 1; k < tour_size; ++k) {
				int new_distance = threeOptSwap(g, tour, i, j, k);
				
				if (new_distance < 0) {
					best_distance += new_distance;
					return true;
				}
			}
		}
	}

	return false;
}

int threeOptSwap(std::vector< std::vector<int> > &g, std::vector<int> &tour, int i, int j, int k) {
	
	/*
		Calculates the cost of all of the 7 possible changes to 3 edges and returns the tour created
		by the change with best cost and the difference of the cost of this change. 
	*/

	int tour_size = tour.size();
	int d0 = g[tour[i]][tour[i+1]] + g[tour[j]][tour[j+1]] + g[tour[k]][tour[(k+1) % tour_size]];
	int d1 = g[tour[i]][tour[j]] + g[tour[i+1]][tour[j+1]] + g[tour[k]][tour[(k+1) % tour_size]];
	int d2 = g[tour[i]][tour[i+1]] + g[tour[j]][tour[k]] + g[tour[j+1]][tour[(k+1) % tour_size]];
	int d3 = g[tour[(k+1) % tour_size]][tour[i+1]] + g[tour[j]][tour[j+1]] + g[tour[k]][tour[i]];
	int d4 = g[tour[i]][tour[j]] + g[tour[(k+1) % tour_size]][tour[j+1]] + g[tour[k]][tour[i+1]];
	int d5 = g[tour[i]][tour[j+1]] + g[tour[k]][tour[j]] + g[tour[(k+1) % tour_size]][tour[i+1]];
	int d6 = g[tour[i+1]][tour[j+1]] + g[tour[j]][tour[(k+1) % tour_size]] + g[tour[k]][tour[i]];
	int d7 = g[tour[i]][tour[j+1]] + g[tour[i+1]][tour[k]] + g[tour[(k+1) % tour_size]][tour[j]];
	
	if (d0 > d1) {
		std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
		return -d0 + d1;	
	}

	else if (d0 > d2) {
		std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
		return -d0 + d2;
	}

	else if (d0 > d3) {
		std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
		return -d0 + d3;
	}

	else if (d0 > d4) {
		std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
		std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
		return -d0 + d4;
	}

	else if (d0 > d5) {
		std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
		std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
		return -d0 + d5;
	}

	else if (d0 > d6) {
		std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
		std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
		return -d0 + d6;
	}

	else if (d0 > d7) {
		std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
		std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
		std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);	
		return -d0 + d7;
	}

	return d0;	
}

void vnd(std::vector< std::vector<int> > &g, std::vector<int> &tour, int &distance) {
	
	/* 
		VND
		Gets a initial solution as input and uses this to call the 2-Opt local search.
		Searches the 2-opt neighborhood first and when it doesn't have improvements anymore,
		searches the 3-opt neighborhood.
	*/

	std::vector<int> original_tour = tour;
	int original_distance = distance;
	int neigh = 2;
	int i = 0;
	int v1 = 0;
	int v2 = 0;

	while (i < neigh) {
		if (i == 0) {
			while(twoOpt(g, tour, distance));
			
			if (distance < original_distance) {
				original_distance = distance;
				i = 0;
			}

			else i++;
		}

		if (i == 1) {
			while(threeOpt(g, tour, distance));

			if (distance < original_distance) {
				original_distance = distance;
				i = 1;
			}

			else i++;
		}
	}
}

void tabuSearch(std::vector< std::vector<int> > &g, int vertices, std::vector<int> &tour, int &distance) {
	
	/*
		Tabu Search:
		Gets a initial solution as input and uses this to call the 2-Opt local search with tabu search.
		When we find a feasible solution, we check if it's on the tabu list. If it is, we search for a
		new solution. If it's not we update current solution and add current solution to tabu list.
		This runs for a number of iterations 

	*/

	std::vector<int> best_tour = tour;
	std::unordered_map< int, std::vector<int> > tabu_list;

	int threshold = 0;
	int best_distance = distance;
	int tour_size = tour.size();
	int counter = 0;
	int first_counter = 0;
	int tl_size = 0;

	while (threshold < 50) {		
		for (int i = 1; i < tour_size - 1; ++i) {
			for (int j = i + 1; j < tour_size; ++j) {

				std::vector<int> new_tour = twoOptSwap(tour, i, j);

				int new_distance = 0;
				if (j == tour_size - 1) new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[0]] + g[tour[i-1]][tour[j]] + g[tour[0]][tour[i]];
				else new_distance = best_distance - g[tour[i-1]][tour[i]] - g[tour[j]][tour[j+1]] + g[tour[i-1]][tour[j]] + g[tour[j+1]][tour[i]];
					
				if ((new_distance < best_distance)) {
				   	auto it = std::find_if(tabu_list.begin(), tabu_list.end(),
                    [&new_tour](const std::pair<int, std::vector<int> > &p) {
                        return p.second == new_tour;
                    });		

                    if (it == tabu_list.end()) {
                                        	
                    	// Solution is not on tabu_list
                    	if (tl_size > 50) {
                    		tabu_list.erase(first_counter);
                    		first_counter++;
                    		tl_size--;
                    	}

                    	tabu_list.insert(std::make_pair(counter, new_tour));
                    	counter++;
                    	tour = new_tour;
                    	best_distance = new_distance;
                    	distance = best_distance;
                    	tl_size++;
                    	break;
                    }
				} 
			}
		}	

		threshold++;
	}
}