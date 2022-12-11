#include "graph.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <random>

/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices.
std::vector<int> tsp(const Graph &graph, int start_vertex);
//std::vector<int> tsp_bruteforce(const Graph& graph, int start_vertex); 

std::pair<int, std::vector<int>> naive(const Graph &graph, int start_vertex);

std::vector<int> greedy_tsp(const Graph &graph, int start_vertex);

std::vector<bool> naive_tests();
std::vector<bool> tsp_tests();

std::vector<int> min_dir(const std::vector<int> &path);

double pathLengthCount(const Graph &graph, std::vector<int> permutation);