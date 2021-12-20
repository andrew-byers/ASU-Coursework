/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: file to run the race logic
*/


#include "byers_race.h"
#include "byers_racer.h"
#include "byers_segments.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

//If the user wants to run a random race, nullptr for use with destructor
Race::Race(){
    this->length = rand() % 40 + 10;   
    this->trackArray = nullptr;
    this->racerArray = nullptr;
} 

//If the user inputs a length, nullptr for use with destructor
Race::Race(int userLength){
    this->length = userLength;
    this->trackArray = nullptr;
    this->racerArray = nullptr;
}

//Destructor, deletes dynamic trackArray and racerArray
Race::~Race(){
    for(int i = 0; i <= this->length; i++){
        delete trackArray[i];
    }
    delete[] trackArray;
    for(int i = 0; i < 8; i++){
        delete racerArray[i];
    }
    delete[] racerArray;
}

void Race::RunRace(){
    trackArray = new RoadSegment*[length];
    cout << "STARTING RACE WITH " << length << " UNITS" << endl;
    //Randomly select the first road segment
    int first = rand() % 4 + 1;
    if(first == 1){
        trackArray[0] = new AsphaltSegment();
    }
    else if(first == 2){
        trackArray[0] = new CrumbledSegment();
    }
    else if(first == 3){
        trackArray[0] = new GravelSegment();
    }
    else{
        trackArray[0] = new DirtSegment();
    }

    cout << "Here's the track..." << endl;
    //Generate the track
    for(int i = 1; i <= length; i++){
        trackArray[i] = trackArray[i-1]->generateNeighbor();
        cout << trackArray[i]->toString();
    }

    //Make an array of 8 random racers, and zero out their positions
    cout << "The racers are...\n\n";
    racerArray = new Racer*[8];
    int racerPosition[8];
    for(int i = 0; i < 8; i++){
        int racerVal = rand() % 3 + 1;
        if(racerVal == 1){
            racerArray[i] = new StreetRacer();
        }
        else if(racerVal == 2){
            racerArray[i] = new SteadyRacer();
        }
        else{
            racerArray[i] = new ToughRacer();
        }
        racerArray[i]->setCarNumber(i+1);
        racerPosition[i] = 0;
        cout << racerArray[i]->toString() << endl;
    }

    bool noWinner = true;
    int loopCount = 1;
    int winnerIndex = -1;

    //Begin race sequence
    while(noWinner){
        cout << "********************************************" << endl;
        cout << "Update " << loopCount << "!" << endl;
        cout << "--------" << endl;
        //Loop through every racer, see if they make progress, and if it constitutes a win
        for(int i = 0; i < 8; i++){
            Racer* currentRacer = racerArray[i];
            RoadSegment* currentSegment = trackArray[racerPosition[i]];

            //Should the Racer progress to the next segment?
            if(currentRacer->getCurrentProgress() >= currentSegment->getLength()){
                currentRacer->resetProgress();
                racerPosition[i] += 1;
            }
            //Should the Racer win?
            if(racerPosition[i] >= length){
                noWinner = false;
                winnerIndex = i+1;
                break;
            }
            //Otherwise, make them progress
            else{
                currentRacer->makeProgress(currentSegment->getModifier());
            }
            cout << currentRacer->toString() << " units into Segment #" << racerPosition[i] << " " << trackArray[racerPosition[i]]->toString();
        }
           
        //End of loop outputs
        cout << "Track: " << endl;
        for(int i = 0; i < length; i++){
            if(trackArray[i]->getModifier() >= 1.0){
                cout << " A ";
            }
            else if(trackArray[i]->getModifier() >= 0.6 && trackArray[i]->getModifier() <= 0.8){
                cout << " C ";
            }
            else if(trackArray[i]->getModifier() >= 0.3 && trackArray[i]->getModifier() <= 0.6){
                cout << " G ";
            }
            else if(trackArray[i]->getModifier() >= 0 && trackArray[i]->getModifier() <= 0.3){
                cout << " D ";
            }
            else{
                cout << " # ";
            }
            if(i != length-1){
                cout << "-";
            }  
        }
        cout << endl;
        loopCount++;
        
    }
    //Announce winner
    cout << "The winner is car number " << winnerIndex << "!" << endl;
    
}
