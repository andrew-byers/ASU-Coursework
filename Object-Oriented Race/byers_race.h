/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: header for the race logic
*/



#pragma once
#ifndef RACE_H
#define RACE_H

#include <iostream>
#include "byers_segments.h"
#include "byers_racer.h"
using namespace std;

class Race{
    public:
        Race();
        Race(int userLength);
        ~Race();
        void RunRace();
        int length;
        RoadSegment** trackArray;
        Racer** racerArray;
};

#endif