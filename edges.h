#pragma once
#include <string>
#include <vector>

using namespace std;

class Edge {
    public:
    void addEdge(string origin, string dest, double weight);
    void printEdgeWeights();

    private:
    map<string, vector<pair<string, double>>> edges_map; //Map that contains all the weights of the edges between airports
};