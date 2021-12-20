/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: header for different segments
*/




#pragma once
#ifndef ROADSEGMENT_H
#define ROADSEGMENT_H

#include <iostream>
#include <string>
using namespace std;

class RoadSegment {
    protected:
        int length;
        double modifier;

    public:
        RoadSegment();
        virtual RoadSegment* generateNeighbor() = 0;
        int getLength();
        double getModifier();  
        virtual string toString();
};

class AsphaltSegment: public RoadSegment {
    public:
        AsphaltSegment();
        RoadSegment* generateNeighbor();
        int getLength();
        double getModifier();
        string toString();
};

class CrumbledSegment: public RoadSegment {
    public: 
        CrumbledSegment();
        RoadSegment* generateNeighbor();
        int getLength();
        double getModifier();
        string toString();
};

class GravelSegment: public RoadSegment {
    public:
        GravelSegment();
        RoadSegment* generateNeighbor();
        int getLength();
        double getModifier();
        string toString();
    };

class DirtSegment: public RoadSegment {
    public:
        DirtSegment();
        RoadSegment* generateNeighbor();
        int getLength();
        double getModifier();
        string toString();
};

#endif