/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: header for racer objects
*/


#pragma once
#ifndef RACER_H
#define RACER_H

#include <iostream>
#include <string>
using namespace std;


class Racer{
    protected:
        int carNumber;
        double speed;
        double currentProgress;
    public:
        Racer();
        int getCarNumber();
        double getSpeed();
        double getCurrentProgress();
        void resetProgress();
        void virtual makeProgress(double modifier) = 0;
        void setCarNumber(int num);
        virtual string toString();
};

class StreetRacer: public Racer{
    public:
        StreetRacer();
        void makeProgress(double modifier);
        string toString();
};

class SteadyRacer: public Racer{
    public:
        SteadyRacer();
        void makeProgress(double modifier);
        string toString();
};

class ToughRacer: public Racer{
    public:
        ToughRacer();
        void makeProgress(double modifier);
        string toString();
};


#endif