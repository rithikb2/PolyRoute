#pragma once
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <tuple>

using namespace std;

class Edge {
    public:
    Edge(string origin, string dest, double weight, double angle);
    //~Edge();
    void addEdge(map<string, vector<tuple<string, double, double>>> edges_map);
    
    //void printEdgeWeights();

    private:
    string edge_origin;
    string edge_dest;
    double edge_weight;
    double edge_angle; 
};