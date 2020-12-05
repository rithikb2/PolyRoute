#pragma once
#include <string>
#include <vector>
#include <utility>
#include<map>

using namespace std;

class Vertex {

    public:
    Vertex(string iata, double lati, double longi);
    ~Vertex();
    void assignSector()
    double getLati();
    double getLongi();

    private:
    string iata;
    double lati;
    double longi;
    map<int, vector<string>> out_angles;
};