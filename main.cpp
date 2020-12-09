#include <iostream>
#include <string>
#include "map_route.h"

using namespace std;

int main( int argc, const char* argv[] )
{
    int sides;
    cout << "How many sides does your shape have? (>2)" << "\n";
    cin >> sides;
    while (sides <= 2) {
        cout << "Invalid number of sides for a polygon" << "\n" 
            << "How many sides does your shape have?" << "\n";
        cin >> sides;
    }

    double tangles = (sides - 2) * 180;
    double angle;
    vector<double> angles;

    string ending;
    for (int i = 1; i <= sides; i++) {
        if (i == 1) {
            ending = "st";
        }
        if (i == 2) {
            ending = "nd";
        }
        if (i == 3) {
            ending = "rd";
        } 
        if (i > 3) {
            ending = "th";
        }
    
        cout << "What is the degree of the " << i << ending + " inner angle ? [1, " << 
            (int)(tangles > 179 ? 179 : tangles) << "] \n";
        cin >> angle;
        
        if (angle >= 180 || angle <= 0 || angle > tangles) {
            cout << "Invalid angle for a polygon" << "\n";
            i--;
        } else {
            tangles -= angle;
            angles.push_back(angle);
        }
    }
    
    
    return 0;
}


