/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: definitions of different segments and their properties
*/




#include "byers_segments.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//Default Contrusctors for all RoadSegment types (and RoadSegment)
RoadSegment::RoadSegment(){
    length = rand() % 40 + 10;
    modifier = 0;
}

AsphaltSegment::AsphaltSegment(){
    this -> modifier = 1;
}

CrumbledSegment::CrumbledSegment(){
    double modRand = rand() % 3 + 6;
    this -> modifier = modRand/10;
}

GravelSegment::GravelSegment(){
   double modRand = rand() % 4 + 3; 
   this -> modifier = modRand/10;
}

DirtSegment::DirtSegment(){
    double modRand = rand() % 4;
    this -> modifier = modRand/10;
}

//generateNeighbor implementations for children of RoadSegment
RoadSegment* AsphaltSegment::generateNeighbor(){
    //random number from 1 to 100
    int rando = rand() % 100 + 1;
    RoadSegment* neighbor;
    //Check which should be the neighbor (percentage chances)
    if(rando >=1 && rando <= 60){
        neighbor = new AsphaltSegment(); 
    }
    else if(rando > 60 && rando <=85){
        neighbor = new CrumbledSegment();
    }
    else if(rando > 85 && rando <=95){
        neighbor = new GravelSegment();
    }
    else if(rando > 95 && rando <= 100){
        neighbor = new DirtSegment();
    }
    return neighbor;
}

RoadSegment* CrumbledSegment::generateNeighbor(){
    //random number from 1 to 100
    int rando = rand() % 100 + 1;
    RoadSegment* neighbor;
    //Check which should be the neighbor (percentage chances)
    if(rando >=1 && rando <= 40){
        neighbor = new CrumbledSegment();
    }
    else if(rando > 40 && rando <=65){
        neighbor = new AsphaltSegment();
    }
    else if(rando > 65 && rando <=90){
        neighbor = new GravelSegment();
    }
    else if(rando > 90 && rando <= 100){
        neighbor = new DirtSegment();
    }
    return neighbor;
}

RoadSegment* GravelSegment::generateNeighbor(){
    //random number from 1 to 100
    int rando = rand() % 100 + 1;
    RoadSegment* neighbor;
    //Check which should be the neighbor (percentage chances)
    if(rando >=1 && rando <= 50){
        neighbor = new GravelSegment();   
    }
    else if(rando > 50 && rando <= 85){
        neighbor = new DirtSegment();   
    }
    else if(rando > 85 && rando <= 95){
        neighbor = new CrumbledSegment();    
    }
    else if(rando > 95 && rando <= 100){
        neighbor = new AsphaltSegment();    
    }
    return neighbor;
}

RoadSegment* DirtSegment::generateNeighbor(){
    //random number from 1 to 100
    int rando = rand() % 100 + 1;
    RoadSegment* neighbor;
    //Check which should be the neighbor (percentage chances)
    if(rando >=1 && rando <= 60){
        neighbor = new DirtSegment(); 
    }
    else if(rando > 60 && rando <= 90){
        neighbor = new GravelSegment();
    }
    else if(rando > 90 && rando <= 95){
        neighbor = new CrumbledSegment();
    }
    else if(rando > 95 && rando <= 100){
        neighbor = new AsphaltSegment();
    }
    return neighbor;
}

//getLength() implementations

int RoadSegment::getLength(){
    return this -> length;
}

//getModifier() implementations

double RoadSegment::getModifier(){
    return this -> modifier;
}

//toString declarations following output format:
//     "(Type) - (Length)"
string AsphaltSegment::toString(){
    return "Asphalt - " + to_string(this->length) + " units\n";
}

string CrumbledSegment::toString(){
    return "Crumbled - " + to_string(this->length) + " units\n";
}

string GravelSegment::toString(){
    return "Gravel - " + to_string(this->length) + " units\n";
}

string DirtSegment::toString(){
    return "Dirt - " + to_string(this->length) + " units\n";
}

string RoadSegment::toString(){
    return "This is a default toString()\n";
}