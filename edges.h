#pragma once
#include <string>
#include <vector>
#include <utility>
#include<map>

using namespace std;

class Edge {
    public:
    Edge(string origin, string dest, double weight);
    ~Edge();
    void addEdge(map<string, vector<pair<string, double>>> edges_map, map<string, map<string, double>> mapRoute2d);
    
    //void printEdgeWeights();

    private:
    string edge_origin;
    string edge_dest;
    double edge_weight;
};