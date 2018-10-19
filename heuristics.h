#include <limits>
#include <set>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include "graph.h"

int nearestNeighbor(Graph &g, int source, std::vector<int> &tour);
std::vector<int> twoOptSwap(std::vector<int> tour, int i, int k);
int tourDistance(Graph &g, std::vector<int> &tour);
int tourDistanceM(std::vector< std::vector<int> > &g, std::vector<int> tour);
std::vector<int> twoOptSwap(std::vector<int> tour, int i, int k);
bool twoOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int &best_distance);
bool threeOpt(std::vector< std::vector<int> > &g, std::vector<int> &tour, int &best_distance);
int threeOptSwap(std::vector< std::vector<int> > &g, std::vector<int> &tour, int i, int j, int k);
void vnd(std::vector< std::vector<int> > &g, std::vector<int> &tour, int &distance);
void tabuSearch(std::vector< std::vector<int> > &g, int vertices, std::vector<int> &tour, int &distance);
