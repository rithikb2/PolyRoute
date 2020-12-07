#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cmath>
#include <math.h>

#include "obtain_path.h"
#include "map_route.h"
#include "vertex.h"

/*
* @Param vector of vectors of possible path solutions
* Given a vector of vectors of s
* Assume this is in map_route and we have access to variables/classes in map_route
*/
int ObtainPath::pickPath(vector<vector<string>> solutions) {
    double minPerimeter;
    bool firstTime = true;
    int solution; //Index of shortest path
    for (size_t i = 0; i < solutions.size(); i++) {
        vector<Vertex> currVertices;
        double currPerimeter = 0;
        for (size_t j = 0; j < solutions[i].size(); j++) {
            Vertex currVertex = vertices_map[solutions[i][j]];
            currVertices.push_back(currVertex);
        }
        for (size_t j = 0; j < currVertices.size(); j++) {
            if (j == currVertices.size() - 1) {
                //Get Distance from last vertex to the first vertex
                double edgeDist = getDistance(vertices_map[solutions[i][j]], vertices_map[solutions[i][0]]);
                currPerimeter += edgeDist;
            } else {
                //Get Distance from current vertext to next vertex
                double edgeDist = getDistance(vertices_map[solutions[i][j]], vertices_map[solutions[i][j+1]]);
                currPerimeter += edgeDist;
            }
        }
        if (firstTime) {
            minPerimeter = currPerimeter;
            solution = 0;
            firstTime = false;
        } else if (currPerimeter < minPerimeter) {
            minPerimeter = currPerimeter;
            solution = i;
        } else {
            continue;
        }
    }
    return solution;
}

vector<string> modifyPath(vector<string> currPath) {
    
}

double ObtainPath::getDistance(Vertex origin, Vertex dest) {
    //For Weight, we could use Haversine formula to convert lat & long to distance
    double earth_radius = 6371; //km
    double lat_origin = origin.getLati() * M_PI/180; //radians
    double lat_dest = dest.getLati() * M_PI/180; //radians
    double lat_difference = (origin.getLati() - dest.getLati()) * M_PI/180;
    double long_difference = (origin.getLongi() - dest.getLongi()) *M_PI/180;
    double haversine = sin(lat_difference/2)*sin(lat_difference/2) + cos(lat_origin) * cos(lat_dest) * sin(long_difference/2) * sin(long_difference/2);
    double c = 2*atan2(sqrt(haversine), sqrt(1-haversine));
    double distance = earth_radius * c; //Can potentially be used for weight between two airports (distance in km) 
    return distance;
}