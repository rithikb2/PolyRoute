#pragma once
#include <string>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class Vertex {

    public:
    Vertex();
    Vertex(string iata, double lati, double longi);
    //~Vertex();
    void assignSector(double angle, string dest);
    string getIata();
    double getLati();
    double getLongi();
    map<int, vector<string>> getAngles();

    private:
    static const int DOF = 5;
    string iata;
    double lati;
    double longi;
    map<int, vector<string>> out_angles;
};