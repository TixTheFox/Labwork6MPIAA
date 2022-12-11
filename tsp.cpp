#include "tsp.h"

using namespace std;


double pathLengthCount(const Graph &graph, vector<int> permutation)
{
    double pathLength = 0;

    for (int i = 0; i < permutation.size() - 1; i++)
    {
        pathLength += graph.edge_weight(permutation[i], permutation[i+1]);
    }

    return pathLength;
}


//full iteration over verties permutations with fixed starting vertex
pair<int, vector<int>> naive(const Graph &graph, int start_vertex)
{
    //Get vertices as vector and make start_vertex first in this vector
    vector<int> verts = graph.get_vertices();
    if (verts.size() < 2)
    {
        return {0, vector<int> {}};
    }
    int startIndex = find(verts.begin(), verts.end(), start_vertex) - verts.begin();
    swap(verts[0], verts[startIndex]);
    //verts.push_back(start_vertex);
    
    double minPathLength = 100000000;
    vector<int> minPath(0);

    do 
    {
            double currentPath = pathLengthCount(graph, verts);
            if ((currentPath < minPathLength) && (currentPath > 0))
            {
                minPathLength = currentPath;
                minPath = verts;
            }
        }while(next_permutation(verts.begin() + 1, verts.end()));

    
    if (minPath.size() > 0)
    {
        //minPath.pop_back();
        return {minPathLength, minPath};
    }
    return {0, vector<int> ()};
}

//returns a path with min length
vector<int> MinPath(const Graph &graph, const vector<int> path1, const vector<int> path2)
{
    return (pathLengthCount(graph, path1) < pathLengthCount(graph, path2) ? path1 : path2);
}

//returns tow adjacent to given vertex edges with minimal sum wight
double getTwoMinEdges(const Graph &graph, const vector<int> &visited, int vertex)
{
    vector<int> adjacent_verts = graph.get_adjacent_vertices(vertex);
    vector<double> edge_weights {};
    for (int i : adjacent_verts)
    {
        if (find(visited.begin(), visited.end(), i) == visited.end())
        {
            edge_weights.push_back(graph.edge_weight(i, vertex));
        }
    }
    if (edge_weights.size() == 1)
    {
        return edge_weights[0];
    }else if (edge_weights.size() > 1)
    {
        sort(edge_weights.begin(), edge_weights.end());
        return edge_weights[0] + edge_weights[1];
    }
    
    return 0;

}

double LowerBound(const Graph &graph, const vector<int> &visited)
{
    double pathEstimation = 0;
    vector<int> verts = graph.get_vertices();

    for (int i : verts)
    {
        if (find(visited.begin(), visited.end(),i) == visited.end())
        {
            pathEstimation += getTwoMinEdges(graph, visited, i);
        }
    }

    pathEstimation /= 2;
    //pathEstimation += pathLengthCount(graph, visited);
    return pathEstimation;
}

vector<int> BnB(const Graph &graph, const vector<int> &visited, vector<int> &bestPath)
{
    if (visited.size() == graph.get_vertices().size())
    {
       return MinPath(graph, visited, bestPath);
    }

    vector<int> verts = graph.get_vertices();

    for (int i : verts)
    {
        if (find(visited.begin(), visited.end(),i) == visited.end())
        {
            vector<int> VNext = visited;
            VNext.push_back(i);
            if (LowerBound(graph, VNext) < pathLengthCount(graph, bestPath))
            {
                vector<int> path = BnB(graph, VNext, bestPath);
                bestPath = MinPath(graph, bestPath, path);
            }

        }
    }
    return bestPath;
}


vector<int> tsp(const Graph &graph, int start_vertex) 
{
    vector<int> bestPath = graph.get_vertices();
    vector<int> visited = {start_vertex};
    if (bestPath.size() < 2)
    {
        return {};
    }
    return BnB(graph, visited, bestPath);
}



//greedy solution
vector<int> greedy_tsp(const Graph &graph, int start_vertex)
{
    vector<int> path = {start_vertex};
    int current_vert = start_vertex;
    while(path.size() != graph.get_vertices().size())
    {
        vector<int> adj_edges = graph.get_adjacent_vertices(current_vert);
        int current_min = 0;
        for (int i : adj_edges)
        {
            if (find(path.begin(), path.end(), i) == path.end()){
                current_min = i;
                break;
            }
        }
        for (int i : adj_edges)
        {
            if ((graph.edge_weight(current_min, current_vert) > graph.edge_weight(i, current_vert)) &&
                (find(path.begin(), path.end(), i) == path.end()))
            {
                current_min = i;
            }
        }
        path.push_back(current_min);
        current_vert = current_min;
    }

    return path;
}