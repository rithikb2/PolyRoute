#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iterator>

#include "edges.h"

using namespace std;

void Edge::addEdge(string origin, string dest, double weight) {
    //Check if origin key exists in map
    if (edges_map.find(origin) == edges_map.end()) {
        //Doesn't Exist in Map Yet
        pair<string, double> newPair(make_pair(dest, weight));
        vector<pair<string, double>> newVector;
        newVector.push_back(newPair);
        edges_map[origin] = newVector;
    } else {
        //Exists in Map Already
        pair<string, double> newPair(make_pair(dest, weight));
        edges_map[origin].push_back(newPair);
    }
}

void Edge::printEdgeWeights() {
    for (map<string, vector<pair<string, double>>>::const_iterator it = edges_map.begin(); it != edges_map.end(); it++) {
        cout<<"Origin Airport: " << it->first<<endl;
        for (int i = 0; i < it->second.size(); i++) {
            cout<<"Dest: " <<it->second.at(i).first<<"  "<<"Weight: "<<it->second.at(i).second<<endl;
        }
        cout<<endl;
    }
}