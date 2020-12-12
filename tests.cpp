#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <cstdlib>
#include <cmath>

#include "catch/catch.hpp"
#include "edges.h"
#include "map_route.h"
#include "vertex.h"

using namespace std;

MapRoute createMapRoute() {
    string routeData = "routes.dat.txt";
    string airlineData = "airlines.dat.txt";
    vector<double> angles;
    angles.push_back(100);
    angles.push_back(70);
    angles.push_back(80);
    angles.push_back(110);
    MapRoute myRoute(routeData, airlineData, 4, angles);
    return myRoute;
}

//A valid edge is made
TEST_CASE("Test if valid edge is made", "[weight=1]") {
    Edge myEdge("SFO", "LAX", 275, 86.2);
    REQUIRE(myEdge.getOrigin() == "SFO");
    REQUIRE(myEdge.getDest() == "LAX");
    REQUIRE(myEdge.getDistance() == 275);
    REQUIRE(myEdge.getAngle() == 86.2);
}

//Test if addEdge() works
TEST_CASE("Test add an edge to edges_map-simple", "[weight=1]") {
    Edge myEdge("SFO", "LAX", 275, 86.2);
    map<string, vector<tuple<string, double, double>>> edges_map;
    myEdge.addEdge(edges_map);
    REQUIRE(get<0>(edges_map["SFO"][0]) == "LAX");
    REQUIRE(get<1>(edges_map["SFO"][0]) == 275);
    REQUIRE(get<2>(edges_map["SFO"][0]) == 86.2);
}

//Test if addEdge() works with multiple edges of the same origin airport
TEST_CASE("Test edge with one origin and multiple destinations", "[weight=1]") {
    Edge first("SFO", "LAX", 275, 86.2);
    Edge second("SFO", "ORD", 418, 22.1);
    Edge third("SFO", "MIA", 645.1, 42.7);
    map<string, vector<tuple<string, double, double>>> edges_map;
    first.addEdge(edges_map);
    second.addEdge(edges_map);
    third.addEdge(edges_map);
    REQUIRE(get<0>(edges_map["SFO"][0]) == "LAX");
    REQUIRE(get<1>(edges_map["SFO"][0]) == 275);
    REQUIRE(get<2>(edges_map["SFO"][0]) == 86.2);
    REQUIRE(get<0>(edges_map["SFO"][1]) == "ORD");
    REQUIRE(get<1>(edges_map["SFO"][1]) == 418);
    REQUIRE(get<2>(edges_map["SFO"][1]) == 22.1);
    REQUIRE(get<0>(edges_map["SFO"][2]) == "MIA");
    REQUIRE(get<1>(edges_map["SFO"][2]) == 645.1);
    REQUIRE(get<2>(edges_map["SFO"][2]) == 42.7);
}

//Test if addEdge() works with multiple edges of different origin airports
TEST_CASE("Test edge with multiple origins and destinations", "[weight=1]") {
    Edge first("SFO", "LAX", 275, 86.2);
    Edge second("ORD", "DFW", 246, 110.4);
    Edge third("LGA", "MIA", 367, 87.9);
    map<string, vector<tuple<string, double, double>>> edges_map;
    first.addEdge(edges_map);
    second.addEdge(edges_map);
    third.addEdge(edges_map);
    REQUIRE(get<0>(edges_map["SFO"][0]) == "LAX");
    REQUIRE(get<1>(edges_map["SFO"][0]) == 275);
    REQUIRE(get<2>(edges_map["SFO"][0]) == 86.2);
    REQUIRE(get<0>(edges_map["ORD"][0]) == "DFW");
    REQUIRE(get<1>(edges_map["ORD"][0]) == 246);
    REQUIRE(get<2>(edges_map["ORD"][0]) == 110.4);
    REQUIRE(get<0>(edges_map["LGA"][0]) == "MIA");
    REQUIRE(get<1>(edges_map["LGA"][0]) == 367);
    REQUIRE(get<2>(edges_map["LGA"][0]) == 87.9);
}

//A valid vertex is made
TEST_CASE("Test if proper vertex is made", "[weight=1]") {
    Vertex myVertex("LAX", 33.94, 118.40);
    REQUIRE(myVertex.getLati() == 33.94);
    REQUIRE(myVertex.getLongi() == 118.40);
}

//Test if getDistance() returns the correct distance
TEST_CASE("Test if getDistance returns correct distance", "[weight=1]") {
    MapRoute myRoute = createMapRoute();
    Vertex la("LAX", 33.94, 118.4);
    Vertex chi("ORD", 41.97, 87.91);
    double distance = myRoute.getDistance(la, chi);
    double actualDistance = 2753; //in KM
    REQUIRE(abs(distance - actualDistance) < 600);
}

//Test if getAngle() returns correct angle
TEST_CASE("Test if getAngle returns correct angle", "[weight=1]") {
    MapRoute myRoute = createMapRoute();
    Vertex la("LAX", 33.94, 118.4);
    Vertex chi("ORD", 41.97, 87.91);
    double angle = myRoute.getAngle(la, chi);
    double expected = 162.39; //in degrees
    REQUIRE(abs(angle - expected) < 20);
}

//Test if map_route works properly (DFS)
TEST_CASE("Test map_route creation", "[weight=1]") {
    MapRoute myRoute = createMapRoute();
    myRoute.findPaths();
    int solution_index = myRoute.pickPath();
    vector<vector<string>> theSolutions = myRoute.getSolutions();
    vector<string> solution = theSolutions[solution_index];
    REQUIRE(solution.size() == 4);
}

//Test if algorithms (DFS & Landmark) work properly
TEST_CASE("Test algorithms", "[weight=1]") {
    MapRoute myRoute = createMapRoute();
    myRoute.findPaths();
    int solution_index = myRoute.pickPath();
    vector<vector<string>> theSolutions = myRoute.getSolutions();
    vector<string> solution = theSolutions[solution_index];
    myRoute.modifyPath(solution);
    REQUIRE(solution[0] == "CLE");
    REQUIRE(solution[1] == "RIC");
    REQUIRE(solution[2] == "CLT");
    REQUIRE(solution[3] == "DTW")
}