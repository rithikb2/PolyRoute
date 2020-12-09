#pragma once

#include <vector>
#include <string>

#include "vertex.h"

class ObtainPath {
    public:
    int pickPath(vector<vector<string>> solutions);
    double getDistance(Vertex origin, Vertex dest);
    double getAngle(Vertex origin, Vertex dest);
    bool pathExist(string origin, string dest);
    vector<string> modifyPath(vector<string> currPath);
    map<string, Vertex> vertices_map;
    map<string, vector<tuple<string, double, double>>> edges_map;
};