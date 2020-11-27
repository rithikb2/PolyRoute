#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream in("/home/adammn2/final_project/routes.dat.txt");
    string line;
    int count = 0;
    while(getline(in, line) && count < 4) {
        stringstream linestream(line);
        string airline, airline_id, source_airport, source_airport_id, dest_airport, dest_airport_id,
        codeshare, stops, equipment;
        getline(linestream, airline, ',');
        getline(linestream, airline_id, ',');
        getline(linestream, source_airport, ',');
        getline(linestream, source_airport_id, ',');
        getline(linestream, dest_airport, ',');
        getline(linestream, dest_airport_id, ',');
        getline(linestream, codeshare, ',');
        getline(linestream, stops, ',');
        getline(linestream, equipment, ',');
        /*
        if (codeshare.empty()) {
            cout << "Codeshare is NULL" << endl;
        } else {
            cout << "Codeshare : " << codeshare << endl;
        }
        */

       //Print routes with more than 0 stops 
       /* 
       stringstream convert_int(stops);
       int stops_int = 0;
       convert_int >> stops_int;
       if (stops_int != 0) {
           cout << "Source Airport: " << source_airport << endl << "Destination Airport: " << dest_airport << endl << "Stops: " << stops << endl;
           count++;
       }
       */
        
        //Prints basic info
        cout << "Source Airport: " << source_airport << endl << "Destination Airport: " << dest_airport << endl << "Stops: " << stops << endl;
        count++;
        
    }
}