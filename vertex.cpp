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
    if ((int) angle/5 == 0) {
        angle = 360;
    }
    vector<string> &sectorIDs  = out_angles[(int) angle/5];
    sectorIDs.push_back(dest);
}

double Vertex::getLati() {
    return this->lati;
}
double Vertex::getLongi() {
    return this->longi;
}

