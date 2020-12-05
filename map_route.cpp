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
MapRoute::MapRoute(string route_dataset_path, string airline_dataset_path) {
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
        vertices_map[IATA] = new Vertex(IATA, stod(latitude), stod(longitude));
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
        Edge newEdge(source_airport, dest_airport, distance, angle); //Made a default weight-change this later!
        newEdge.addEdge(edges_map); //Add newly created edge to our map of edges
    }

}

double MapRoute::getDistance(Vertex origin, Vertex dest) {
    //For Weight, we could use Haversine formula to convert lat & long to distance
    double earth_radius = 6371; //km
    double lat_origin = origin.lati * M_PI/180; //radians
    double lat_dest = dest.lati * M_PI/180; //radians
    double lat_difference = (origin.lati - dest.lati) * M_PI/180;
    double long_difference = (origin.longi - dest.longi) *M_PI/180;
    double haversine = sin(lat_difference/2)*sin(lat_difference/2) + cos(lat_origin) * cos(lat_dest) * sin(long_difference/2) * sin(long_difference/2);
    double c = 2*atan2(sqrt(haversine), sqrt(1-haversine));
    double distance = earth_radius * c; //Can potentially be used for weight between two airports (distance in km) 
    return distance;
}

//37.6, -122.3 foster city, 45.3, -88.7 wisconson
double MapRoute::getAngle(Vertex origin, Vertex dest) {
    double h = getDistance(Vertex origin, Vertex dest);
    double a = getDistance(Vertex origin, Vertex("", dest.getLati(), origin.getLongi()));
    double rad = acos(a/h);
    return (rad * 180/M_PI);
}
