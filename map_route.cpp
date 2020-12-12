#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <math.h>

#include "map_route.h"
using namespace std;

/*
* MapRoute Constructor that takes in our two datasets as strings (path of datasets)
* Saves each of the variables in the datasets
* For the airline dataset, create a node for each airport
* For the route dataset, create a weighted edge for each route. The weighted edge stored in the map of edges
*/
MapRoute::MapRoute(string route_dataset_path, string airline_dataset_path, int sides, vector<double> angles) {
    this->sides = sides;
    this->angles = angles;
    ifstream route_data(route_dataset_path);
    ifstream airline_data(airline_dataset_path);
    //Create Nodes For each Airport
    string airline_line;
    while(getline(airline_data, airline_line)) {
        stringstream linestream(airline_line);
        getline(linestream, index, ',');
        getline(linestream, name, ',');
        getline(linestream, city, ',');
        getline(linestream, country, ',');
        getline(linestream, IATA, ',');
        getline(linestream, ICAO, ',');
        getline(linestream, latitude, ',');
        getline(linestream, longitude, ',');
        getline(linestream, altitude, ',');
        getline(linestream, time_zone, ',');
        getline(linestream, dst, ',');
        getline(linestream, type, ',');
        getline(linestream, source, ',');
        //Node Logic goes here
        //cout << latitude + " :  " + longitude;
        try {
            //cout << "trying";
            stod(latitude);
            stod(longitude);
            Vertex newVertex(IATA, stod(latitude), stod(longitude));
            vertices_map[IATA] = newVertex;
        } catch (const invalid_argument&) {
            //cout << "pass";
            continue;
        }
        //Need to make both a Node, and store the Node in some sort of container
    }

    //Create and Store Edges From Routes
    string route_line;
    while(getline(route_data, route_line)) {
        stringstream linestream(route_line);
        getline(linestream, airline, ',');
        getline(linestream, airline_id, ',');
        getline(linestream, source_airport, ',');
        getline(linestream, source_airport_id, ',');
        getline(linestream, dest_airport, ',');
        getline(linestream, dest_airport_id, ',');
        getline(linestream, codeshare, ',');
        getline(linestream, stops, ',');
        getline(linestream, equipment, ',');
        //Edge Logic goes here
        Vertex origin = vertices_map[source_airport];
        Vertex destination = vertices_map[dest_airport];
        double distance = getDistance(origin, destination);
        double angle = getAngle(origin, destination);
        Edge newEdge(source_airport, dest_airport, distance, angle);
        vertices_map[source_airport].assignSector(angle, dest_airport);
        newEdge.addEdge(edges_map); //Add newly created edge to our map of edges
    }

}

double MapRoute::getDistance(Vertex origin, Vertex dest) {
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

//37.6, -122.3 foster city, 45.3, -88.7 wisconson
double MapRoute::getAngle(Vertex origin, Vertex dest) {
    float dy = dest.getLati() - origin.getLati();
    float dx = cosf(M_PI/180 * origin.getLati()) * (dest.getLongi() - origin.getLongi());
    float angle = atan2f(dy, dx) * 180 / M_PI;
    if (angle < 0) {
        angle += 360;
    }
    return (double) angle;

    /*
    double olat = origin.getLati() * M_PI / 180;
    double olong = origin.getLongi() * M_PI / 180;
    double dlat = dest.getLati() * M_PI / 180;
    double dlong = dest.getLongi() * M_PI / 180;

    double londiff = (dlong - olong);
    double y = sin(londiff) * cos(dlat);
    double x = cos(olat) * sin(dlat) - 
        sin(olat) * cos(dlat) * cos(londiff);

    double angle = atan2(y, x);
    angle = angle * 180/M_PI;
    angle = (int) (angle + 360) % 360;
    angle = 360 - angle;

    return angle;
    
    double h = getDistance(origin, dest);
    double a = getDistance(origin, Vertex("", dest.getLati(), origin.getLongi()));
    double rad = acos(a/h);
    double angle = rad * 180/M_PI;
    if (origin.getLati() > dest.getLati() && origin.getLongi() > dest.getLongi()) {
        return 270 - angle;
    } else if (origin.getLati() > dest.getLati()) {
        return 180 - angle;
    } else if (origin.getLongi() > dest.getLongi()) {
        return 360 - angle;
    }
    return 90 - angle;
    */
}

void MapRoute::findDestinationAngles(Vertex v, int angleNum, 
    pair<int, string> p1, pair<int, string> p2) {
    //rotate through 1 - 360 using two iterators
    //when a match is found with angles[1] return out_angle strings
    if (angleNum == angles.size() - 1) {
        return;
    }

    map<int, vector<string>> sectors = v.getAngles();
    int sector_value = (int) this->angles[angleNum] / DOF;
    int start_sector = 0;
    int end_sector = 360/DOF - 1;

    if (p1.second != "" && p2.second != "") {
        for (int i = 0; i < 360/DOF; i++) {
            for (string j : sectors[i]) {
                if (j == p1.second) {
                    start_sector = i;
                }
                
            }
        }
        for (int i = 0; i < 360/DOF; i++) {
            for (string j : sectors[i]) {
                if (j == p2.second && angleNum == angles.size() - 2) {
                    if (abs(start_sector - i) == sector_value) {
                        potentials.push(v.getIata());
                        potentials.push(p2.second);
                        vector<string> solution = {};
                        while (!potentials.empty()) {
                            solution.push_back(potentials.top());
                            potentials.pop();
                        }
                        //vector<string> solution = {v.getIata(), p1.second, p2.second};
                        for (vector<string> s : solutions) {
                            if (solution == s) {
                                return;
                            }
                        }
                        solutions.push_back(solution);
                        return;
                    } else {
                        potentials.pop();
                    }
                } else {
                    //only p1 is fixed, p2 is freebie
                    if (abs(start_sector - i) == sector_value) {
                        potentials.push(v.getIata());
                        //recurse
                        pair<int, string> pair1 = {i, v.getIata()};
                        pair<int, string> pair2 = p2;

                        Vertex n = vertices_map[j];
                        findDestinationAngles(n, angleNum + 1, pair1, pair2);
                        return;
                    }
                }
            }
        }
        return;
    }

    vector<string> sector_one;
    vector<string> sector_two;

    for (int i = start_sector; i <= end_sector; i++) {
        if (!(sectors[i].empty()) && !(sectors[(i + (sector_value)) % (360/DOF)].empty())) {
            sector_one = sectors[i];
            sector_two = sectors[(i + (sector_value)) % (360/DOF)];
            for (string a : sector_one) {
                for (string b : sector_two) {
                    pair<int, string> pair1 = {i, v.getIata()};
                    pair<int, string> pair2 = {(i + sector_value) % (360/DOF), b};
                    Vertex n = vertices_map[a];
                    potentials = stack<string>();
                    potentials.push(v.getIata());
                    findDestinationAngles(n, angleNum + 1, pair1, pair2);
                }
            }
        }
    }
}


void MapRoute::findPaths() {
    for(map<string,Vertex>::iterator iter = vertices_map.begin(); iter != vertices_map.end(); ++iter) {
        if (resultThreshold == solutions.size()) {
            return;
        }
        findDestinationAngles(vertices_map[iter->first], 0, {0, ""}, {0, ""});
    }
}


/*
* @Param vector of vectors of possible path solutions
* Given a vector of vectors of s
* Assume this is in map_route and we have access to variables/classes in map_route
*/
int MapRoute::pickPath() {
    double minPerimeter;
    bool firstTime = true;
    int solution; //Index of shortest path
    for (int i = 0; i < solutions.size(); i++) {
        double currPerimeter = 0;
        for (int j = 0; j < solutions[i].size(); j++) {
            if (j == solutions[i].size() - 1) {
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

/*
* Modify Path by considering nearby airports
* @Param a vector of strings that represents the current shortest path of the desired shape
* Use Landmark path to determine shortest path from origin to destination through a certain vertex
* Landmark Path: get from Origin to Destination through every 'other' vector (starting with origin)
* Check every other vertex between (not including) origin and destination vertices
* Go through possible edges from that starting airport and find the edges that have a similar degree range to the current 'next stop'
* Then, make sure that that vertex has a path to the airport after
*/
void MapRoute::modifyPath(vector<string> &currPath) {
    //Loop through currPath vector
    for (int i = 0; i < currPath.size(); i++) {
        /*Loop through each vector in edges_map
        * Each vector represents a possible destination from the specific node that we are on
        * Check every even-indexed vector but change every odd-indexed vector (change every other)
        */
        string currentStop = currPath[i];
        if (i % 2 == 0) {
            if (i <= currPath.size() - 2) {
                Vertex currVertex = vertices_map[currentStop]; //Current vertex
                Vertex twoStopsAhead = vertices_map[currPath[i+2]]; //Two vertices down the path
                Vertex oneStopAhead = vertices_map[currPath[i+1]]; //Next Vertex in solution path
                double currAngle = getAngle(currVertex, oneStopAhead); //Angle between current and next vertex
                string nextStop = currPath[i+1];
                string twoStops;
                if (i == currPath.size() - 2) {
                    //Two stops ahead is the origin airport in path
                    twoStops = currPath[0];
                } else {
                    //Two stops ahead is two airports ahead on the route
                    twoStops = currPath[i+2];
                }
                //Loop through the possible destinations of the current vertex
                for (int j = 0; j < edges_map[currentStop].size(); j++) { 
                    //First check if angle is within threshold of 20 degrees
                    //Also check that the alternative is not already the next stop
                    double tempAngle = get<2>(edges_map[currentStop][j]);
                    string tempStop = get<0>(edges_map[currentStop][j]);
                    if (abs(currAngle - tempAngle) <= 20 && nextStop != tempStop) {
                        //Check if there's a path from this alternative stop to the twoStops
                        if (pathExist(tempStop, twoStops)) {
                            //Find new total distance from current stop to alternative stop, and from alternative stop to stop after (twoStops)
                            //See if total new distance is less than original distance between these three stops
                            double currToNext = getDistance(currVertex, oneStopAhead);
                            double nextToTwoAhead = getDistance(oneStopAhead, twoStopsAhead);
                            Vertex tempVertex = vertices_map[tempStop];
                            double currToTempDist = getDistance(currVertex, tempVertex);
                            double TempToNextDist = getDistance(tempVertex, twoStopsAhead);
                            if (currToTempDist + TempToNextDist < currToNext + nextToTwoAhead) {
                                //If so, change next stop to tempStop
                                currPath[i+1] = tempStop;
                            }
                        }
                    }
                }
            }
        }
    }
    return currPath;
}

//Helper function to determine if a path exists between two airports (reference edges_map)
bool MapRoute::pathExist(string origin, string dest) {
    for (int i = 0; i < edges_map[origin].size(); i++) {
        if (get<0>(edges_map[origin][i]) == dest) {
            return true;
        }
    }
    return false;
}

vector<vector<string>> MapRoute::getSolutions() {
    return solutions;
}
