#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

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
        Edge newEdge(source_airport, dest_airport, 32.5); //Made a default weight-change this later!
        newEdge.addEdge(edges_map, routes_map); //Add newly created edge to our map of edges
    }

}
