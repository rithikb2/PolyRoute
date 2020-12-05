#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iterator>

#include "vertex.h"

using namespace std;

Vertex::Vertex(string iata, double lati, double longi) {
    this.iata = iata;
    this.lati = lati;
    this.longi = longi;
}

double Vertex::getLati() {
    return this.lati;
}
double Vertex::getLongi() {
    return this.longi;
}

