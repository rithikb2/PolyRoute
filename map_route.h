#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "vertex.h"
#include "edges.h"

using namespace std;

class MapRoute {
    public:
    MapRoute(string route_dataset_path, string airline_dataset_path);
    //~Maproute();

    private:
    //program return value
    vector<string> finalroute;
    //User inputs number of sides on desired polygon
    int sides;
    /*
    * Contains user inputed angles 
    * Represents the inner angles of a desired polygon
    */
    vector<double> angles;
    //Degrees of freedom for determining a valid edge
    double dof;

    map<string, Vertex> vertices_map;
    /*
    * Our container that stores all of the weighted edges
    * It's a map where the keys are the origin airports (IATA-string)
    * The values for each of the keys is a vector of pairs
    * Each of the pairs contains the destination airport (IATA-string), and the weight of the path from the origin to the destination (double)
    */
    map<string, vector<pair<string, double>>> edges_map; //Map that contains all the weights of the edges between airports.

    /*
    * Container that allows for easier access to the weights of the routes between two airports
    * It's a 2D Map where the first key is the origin airport, the second key is the destination airport, and the value is the weight of the path
    */
    map<string, map<string, double>> routes_map; //2D Map that has the weights of the edges between the airports

    //Define Airport Info String Variables
    string index, name, city, country, IATA, ICAO, latitude, longitude, altitude,
            time_zone, dst, tz_database, type, source;
    //Define Route Info String Variables
    string airline, airline_id, source_airport, source_airport_id, dest_airport, dest_airport_id,
        codeshare, stops, equipment;
    
};