#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>
#include <stack>


#include "vertex.h"
#include "edges.h"

using namespace std;

class MapRoute {
    public:
    MapRoute(string route_dataset_path, string airline_dataset_path, int sides, vector<double> angles);
    //~Maproute();
    double getDistance(Vertex origin, Vertex dest);
    double getAngle(Vertex origin, Vertex dest);
    void findDestinationAngles(Vertex v, int angleNum, pair<int, string> p1, pair<int, string> p2);
    void findPaths();
    int pickPath();
    vector<string> modifyPath(vector<string> currPath);
    bool pathExist(string origin, string dest);
    vector<vector<string>> getSolutions();
    
    private:
    static const int DOF = 5;
    static const int resultThreshold = 20;

    stack<string> potentials;
    //program return value
    vector<string> finalroute;
    //User inputs number of sides on desired polygon
    int sides;
    /*
    * Contains user inputed angles 
    * Represents the inner angles of a desired polygon
    */
    vector<double> angles;

    map<string, Vertex> vertices_map;
    /*
    * Our container that stores all of the weighted edges
    * It's a map where the keys are the origin airports (IATA-string)
    * The values for each of the keys is a vector of tuples
    * Each of the tuples contains the destination airport (IATA-string), and the weight of the path from the origin to the destination (double)
    * The edges_map would have a key (origin airport node) and the values would be a vector of tuples that includes the destination airport node, distance, and angle
    * ex. ORD: [(SFO, 63.4, 200 degrees), (DFW, 43.1, angle)], CDF: [(SHA, 110.5, angle)]
    * Can allow us to hold all the weights in an organized way
    */
    map<string, vector<tuple<string, double, double>>> edges_map; //Map that contains all the weights of the edges between airports.

    /*
    * Container that allows for easier access to the weights of the routes between two airports
    * It's a 2D Map where the first key is the origin airport, the second key is the destination airport, and the value is the weight of the path
    * ex. routes_map[ORD][DFW] = 43.1 or routes_map[CDF][SHA] = 110.5
    * Can allow us to access weights easier if we already know the source and destination airports
    
    map<string, map<string, double>> routes_map; //2D Map that has the weights of the edges between the airports
    */
    vector<vector<string>> solutions;

    //Define Airport Info String Variables
    string index, name, city, country, IATA, ICAO, latitude, longitude, altitude,
            time_zone, dst, tz_database, type, source;
    //Define Route Info String Variables
    string airline, airline_id, source_airport, source_airport_id, dest_airport, dest_airport_id,
        codeshare, stops, equipment;

    
};