#include "tsp.h"

using namespace std;

vector<bool> naive_tests()
{
    vector<bool> result(0);

    //Empty graph
    Graph g {};
    
    result.push_back(naive(g, 0).second == vector<int> {});

    //One-vertex graph
    g.add_vertex(0);

    result.push_back(naive(g, 0).second == vector<int> {});

    //One-edge graph
    g = Graph {{0, 1, 2.5}};

    result.push_back(naive(g, 0).second == vector<int> {0, 1});

    //Three vertices, three edges
    g = Graph {{0, 1, 2.5}, {0, 2, 0.5}, {1, 2, 1.0}};

    result.push_back(naive(g, 0).second == vector<int> {0, 1, 2});

    //Several vertices
    g = Graph {{0, 1, 6.0}, {0, 2, 4.0}, {0, 3, 1.0},
             {1, 2, 3.5}, {1, 3, 2.0}, 
             {2, 3, 5.0}};

    result.push_back(naive(g, 0).second == vector<int> {0, 2, 1, 3});


    //Many vertices
    g = Graph {{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5},
             {1, 2, 3.6}, {1, 3, 6.0}, {1, 4, 3.0}, 
             {2, 3, 7.0}, {2, 4, 5.0}, 
             {3, 4, 9.0}};
    
    result.push_back(naive(g, 0).second == vector<int> {0, 3, 2, 1, 4});


    //Isolated vertices
    g = Graph {{0, 1, 2.5}, {1, 2, 1.0}, {0, 2, 1.0}, {3, 4, 0.7}};

    result.push_back(naive(g, 0).second == vector<int> {});
    result.push_back(naive(g, 3).second == vector<int> {});

    //No looped path
    g = Graph {{0, 1, 2.5}, {0, 2, 1.0}, {2, 3, 7.0} };

    result.push_back(naive(g, 0).second == vector<int> {});
    result.push_back(naive(g, 1).second == vector<int> {});

    return result;
}