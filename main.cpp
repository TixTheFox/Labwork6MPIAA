#include "../catch.hpp"

#include "tsp.h"

#include <chrono>

void printPath(std::vector<int> &s)
{
    for (int i : s)
    {
        std::cout << i << ' ';
    }
}

Graph generateFullGraph(int size)
{
    Graph g;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            double edge = rand() % 10;
            g.add_edge(i, j, edge);
        }
    }
    return g;
}


int main(int argc, char* argv[]) {
    /*
    srand(time(0));
    Graph g = generateFullGraph(10);
    for (int i : g.get_vertices()){
        std::cout << i;
        for (auto j : g.get_adjacent_edges(i)){
            std::cout << "\n\t" << j.first << " " << j.second ; 
        }
        std::cout << std::endl;
    } 
    std::vector<int> res1 = min_dir(naive(g, 0).second);
    std::vector<int> res3 = min_dir(tsp(g, 0));
    std::vector<int> res4 = min_dir(greedy_tsp(g, 0));
    std::cout << "Naive:\n";
    for (auto i : res1){ std::cout << i << " ";}
    std::cout << "\nBnB my:\n";
    for (auto i: res3){std::cout << i << " ";}
    std::cout << "\nGreedy:\n";
    for (auto i: res3){std::cout << i << " ";}
    */

    for (int N = 6; N < 20; N++)
    {
        srand(time(0));
        Graph g = generateFullGraph(N);

        auto t1 = std::chrono::high_resolution_clock::now();	
        int naivePathLength = naive(g, 0).first;
        auto t2 = std::chrono::high_resolution_clock::now();

        auto time = std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();	
        std::vector<int> BnB_path = tsp(g, 0);
        auto t4 = std::chrono::high_resolution_clock::now();

        auto time2 = std::chrono::duration<double>(t4 - t3).count();

        auto t5 = std::chrono::high_resolution_clock::now();	
        std::vector<int> greedyPath = greedy_tsp(g, 0);
        auto t6 = std::chrono::high_resolution_clock::now();

        auto time3 = std::chrono::duration<double>(t6 - t5).count();

        std::cout << "Size (num of vetex in full graph): " << N << "\n";
        std::cout << "\tNaive\n\t path length: " << naivePathLength << "  time: " << time << "\n";
        std::cout << "\tBnb\n\t path length: " << pathLengthCount(g, BnB_path) << "  time: " << time2 << "\n";
        std::cout << "\tGREEDY\n\t path length: " << pathLengthCount(g, greedyPath) << "  time: " << time3 << "\n";
    }
}