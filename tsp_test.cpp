#include "tsp.h"

using namespace std;

vector<int> reversed(const vector<int> &path) {
    if (path.empty()) {
        return vector<int> {};
    }
    vector<int> result = {path[0]}; // first item is a start vertex
    result.insert(result.end(), path.rbegin(), path.rend()); // add vertices in reverse order
    result.pop_back(); // remove duplicated start vertex
    return result;
}

vector<int> min_dir(const vector<int> &path) {
    if (path.size() <= 1) {
        return path;
    }    
    const auto reversed_path = reversed(path);
    return (path[1] <= reversed_path[1] ? path : reversed_path);
}

vector<bool> tsp_tests()
{
    vector<bool> result(0);

    //Empty graph
    Graph g {};
    
    result.push_back(tsp(g, 0) == vector<int> {});

    //One-vertex graph
    g.add_vertex(0);

    result.push_back(tsp(g, 0) == vector<int> {});

    //One-edge graph
    g = Graph {{0, 1, 2.5}};

    result.push_back(tsp(g, 0) == vector<int> {0, 1});

    //Three vertices, three edges
    g = Graph {{0, 1, 2.5}, {0, 2, 0.5}, {1, 2, 1.0}};

    result.push_back(min_dir(tsp(g, 0)) == vector<int> {0, 1, 2});

    //Several vertices
    g = Graph {{0, 1, 6.0}, {0, 2, 4.0}, {0, 3, 1.0},
             {1, 2, 3.5}, {1, 3, 2.0}, 
             {2, 3, 5.0}};

    result.push_back(min_dir(tsp(g, 0)) == vector<int> {0, 2, 1, 3});


    //Many vertices
    g = Graph {{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5},
             {1, 2, 3.6}, {1, 3, 6.0}, {1, 4, 3.0}, 
             {2, 3, 7.0}, {2, 4, 5.0}, 
             {3, 4, 9.0}};
    
    result.push_back(min_dir(tsp(g, 0)) == vector<int> {0, 3, 2, 1, 4});


    //Isolated vertices
    g = Graph {{0, 1, 2.5}, {1, 2, 1.0}, {0, 2, 1.0}, {3, 4, 0.7}};

    try{
        result.push_back(tsp(g, 0) == vector<int> {});
    }
    catch(invalid_argument){
        cout << "Invalid argument on isolated vertices test 1\n";
    }
    try{
        result.push_back(tsp(g, 0) == vector<int> {});
    }
    catch(invalid_argument){
        cout << "Invalid argument on isolated vertices test 2\n";
    }

    //No looped path
    g = Graph {{0, 1, 2.5}, {0, 2, 1.0}, {2, 3, 7.0} };

    try{
        result.push_back(tsp(g, 0) == vector<int> {});
    }
    catch(invalid_argument){
        cout << "Invalid argument on no loop test 1\n";
    }
    try{
        result.push_back(tsp(g, 0) == vector<int> {});
    }
    catch(invalid_argument){
        cout << "Invalid argument on no loop test 2\n";
    }

    return result;
}