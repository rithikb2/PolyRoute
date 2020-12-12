#include <iostream>
#include <string>
#include "map_route.h"

using namespace std;

int main( int argc, const char* argv[] )
{
    int sides;
    cout << "How many sides does your shape have? sides > 2" << "\n";
    cin >> sides;
    while (sides <= 2) {
        cout << "Invalid number of sides for a polygon" << "\n" 
            << "How many sides does your shape have?" << "\n";
        cin >> sides;
    }

    double tangles = (sides - 2) * 180;
    double angle;
    vector<double> angles;
    bool badInput = false;
    string ending;
    int i = 1;
    while (angles.size() != sides) {
        if (badInput) {
            i--;
            badInput = !badInput;
        }
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
        if (i == sides) {
            angles.push_back(tangles);
            break;
        }
        cout << "remaining sum of inner angles: " << tangles << endl;
        cout << "What is the degree of the " << i << ending + " inner angle ? [1, " << 
            (int)(tangles > 179 ? 179 : tangles) << "] \n";
        try {
            cin >> angle;
        } catch (const invalid_argument&) {
            cout << "Invalid angle for a polygon" << "\n";
            badInput = true;
            continue;
        }
        
        if (angle >= 180 || angle <= 0 || angle > tangles) {
            cout << "Invalid angle for a polygon" << "\n";
            badInput = true;
        } else {
            tangles -= angle;
            angles.push_back(angle);
        }
        i++;
    }
    
    MapRoute myRoute = MapRoute("routes.dat.txt", "airlines.dat.txt", sides, angles);
    myRoute.findPaths();
    //solutions are in myRoute.solutions(), call your methods here
    int solution_index = myRoute.pickPath();
    vector<vector<string>> theSolutions = myRoute.getSolutions();
    if (theSolutions.empty()) {
        cout << "Sorry, no solutions were found" <<endl;
        return 0;
    }
    vector<string> solution = theSolutions[solution_index];
    myRoute.modifyPath(solution);
    cout<<"Your final path is: "<<endl;
    for (int i = 0; i < solution.size(); i++) {
        if (i == solution.size() - 1) {
            cout<<shortest_path[i];
        } else {
            cout<<solution[i]<<" -> ";
        }
    }
    cout << endl;
    return 0;
}


