/*
Author: Andrew Byers
ASUID: 1218781876
Date: 11/14/21
Description: definitions of different racer classes, and their properties
*/



#include "byers_racer.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//Racer constructor, and default methods in spec
Racer::Racer(){
    this->carNumber = 0;
    this->speed = 0;
    this->currentProgress = 0;
}

int Racer::getCarNumber(){
    return this->carNumber;
}

double Racer::getSpeed(){
    return this->speed;
}

double Racer::getCurrentProgress(){
    return this->currentProgress;
}

void Racer::resetProgress(){
    this->currentProgress = 0;
}

//Racer type constructors

//*****
StreetRacer::StreetRacer(){
    int randVal = rand() % 25 + 55;
    this->speed = (double)randVal / 10.0;
}

SteadyRacer::SteadyRacer(){
    int randVal = rand() % 10 + 30;
    this->speed = (double)randVal / 10.0;
}

ToughRacer::ToughRacer(){
    int randVal = rand() % 10 + 20;
    this->speed = (double)randVal / 10.0;
}

//Setter for access in Race Logic
void Racer::setCarNumber(int num){
    this->carNumber = num;
}

//makeProgress for all Racer types
void StreetRacer::makeProgress(double modifier){
    this->currentProgress += (this->speed*modifier) + 0.5;
}

void SteadyRacer::makeProgress(double modifier){
    this->currentProgress += this->speed;
}

void ToughRacer::makeProgress(double modifier){
    double bonusSpeed = 5 * (1.0 - modifier);
    this->currentProgress += this->speed + bonusSpeed;
}

//toString() for all racer types
string StreetRacer::toString(){
    return "Racer #" + to_string(this->carNumber) + " Street Car - " + to_string(this->currentProgress) + " units"; 
}

string SteadyRacer::toString(){
    return "Racer #" + to_string(this->carNumber) + " Steady Car - " + to_string(this->currentProgress) + " units";
}

string ToughRacer::toString(){
    return "Racer #" + to_string(this->carNumber) + " Tough Car - " + to_string(this->currentProgress) + " units ";
}

//This should never be called, but it has to exist
string Racer::toString(){
    return "This is a default toString()";
}
