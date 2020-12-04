#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iterator>

#include "edges.h"

using namespace std;
/*
* Edge Constructor that takes in the IATA of the Origin Airport, IATA of Destination, and Weight(distance) of the route
* Edge Constructor that takes in the IATA of the Origin Airport, IATA of Destination, and Weight of the route
* Can change the IATA inputs to simply Node inputs for these edges
* Sets the input variables to their respective private variables
* Creates the Edge Object that can be added to the map with addEdge function
*/
Edge::Edge(string origin, string dest, double weight) {
    edge_origin = origin;
    edge_dest = dest;
    edge_weight = weight;
}

/*
* Adds the newly constructed Edge to the map of Edges
*/
void Edge::addEdge(map<string, vector<pair<string, double>>> edges_map, map<string, map<string, double>> mapRoute2d) {
    //Check if origin key exists in map
    if (edges_map.find(edge_origin) == edges_map.end()) {
        //Doesn't Exist in Map Yet
        pair<string, double> newPair(make_pair(edge_dest, edge_weight));
        vector<pair<string, double>> newVector;
        newVector.push_back(newPair);
        edges_map[edge_origin] = newVector;
    } else {
        //Exists in Map Already
        pair<string, double> newPair(make_pair(edge_dest, edge_weight));
        vector<pair<string, double>> expandedVector = edges_map[edge_origin];
        expandedVector.push_back(newPair);
        edges_map[edge_origin] = expandedVector;
    }
    mapRoute2d[edge_origin][edge_dest] = edge_weight;
}



/*
void Edge::printEdgeWeights() {
    for (map<string, vector<pair<string, double>>>::const_iterator it = edges_map.begin(); it != edges_map.end(); it++) {
        cout<<"Origin Airport: " << it->first<<endl;
        for (int i = 0; i < it->second.size(); i++) {
            cout<<"Dest: " <<it->second.at(i).first<<"  "<<"Weight: "<<it->second.at(i).second<<endl;
        }
        cout<<endl;
    }
}
*/
