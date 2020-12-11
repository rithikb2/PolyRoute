#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iterator>

#include "vertex.h"

using namespace std;

Vertex::Vertex() {}

Vertex::Vertex(string iata, double lati, double longi) {
    this->iata = iata;
    this->lati = lati;
    this->longi = longi;
}

void Vertex::assignSector(double angle, string dest) {
    if (out_angles[(int) angle/DOF].empty()) {
        vector<string> sector_ports = {};
    }
    for (string d : out_angles[(int) angle/DOF]) {
        if (d == dest) {
            return;
        }
    }
    out_angles[(int) angle/DOF].push_back(dest);
}

string Vertex::getIata() {
    return this->iata;
}

double Vertex::getLati() {
    return this->lati;
}
double Vertex::getLongi() {
    return this->longi;
}

map<int, vector<string>> Vertex::getAngles() {
    return this->out_angles;
}
