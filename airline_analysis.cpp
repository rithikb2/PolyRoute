#include <iostream>
//#include <"airline_analysis.h">
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream in("/home/adammn2/final_project/airlines.dat.txt");
    string line;
    int count = 0;
    while(getline(in, line) && count < 4) {
        stringstream linestream(line);
        string index, name, city, country, IATA, ICAO, latitude, longitude, altitude,
            time_zone, dst, tz_database, type, source;
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
        
        
        cout << "Name: " << name << endl << "Lat: " << latitude << endl << "Long: " << longitude << endl;
        count++;
    }
    
    
    return 0;
    /*
    if (in.is_open()) {
        cout << in.rdbuf();
    }
    return 0;
    */
}