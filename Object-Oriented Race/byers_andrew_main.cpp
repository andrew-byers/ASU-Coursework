/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: program designed to create either a random race, or a race
    with given length from the user, to simulate a race betwen multiple
    types of cars on multiple types of roads
*/

#include "byers_race.h"
#include "byers_segments.h"
#include "byers_racer.h"
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char** argv){
    srand(time(NULL));

    
    //Prompt the user for selection
    int selection = -1;
    cout << "Welcome to the Racer Derby!" << endl;
    cout << "Would you like to:" << endl;
    cout << "1 - Determine the length of the race" << endl;
    cout << "2 - Run a random race" << endl;
    cout << "-1 - Exit" << endl;
    cin >> selection;

    //User wants to run a race with desired length
    if(selection == 1){
        int desiredLength = 0;
        cout << "What would you like the length to be?\n";
        cin >> desiredLength;
        Race newRace = Race(desiredLength);
        newRace.RunRace();
    }
    //User wants to run a random race
    else if(selection == 2){
        Race newRace = Race();
        newRace.RunRace();
    }
    else{
        return 0;
    }
    return 0;
    //hullo
    
}