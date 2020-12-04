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

    private:
    string iata;
    double lati
    double longi;
};