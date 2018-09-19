#include "graph.h"

int nearestNeighbor(Graph &g, int source, std::vector<int> &tour);
std::vector<int> twoOptSwap(std::vector<int> tour, int i, int k);
int tourDistance(Graph &g, std::vector<int> &tour);
int twoOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int initial_d);