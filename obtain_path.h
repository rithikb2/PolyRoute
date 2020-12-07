#pragma once

#include <vector>
#include <string>

#include "vertex.h"

class ObtainPath {
    public:
    int pickPath(vector<vector<string>> solutions);
    double getDistance(Vertex origin, Vertex dest);
    vector<string> modifyPath(vector<string> currPath);
    map<string, Vertex> vertices_map;
};