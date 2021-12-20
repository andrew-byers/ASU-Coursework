/*
Author: Andrew Byers
Date: 11/24/21
Description: Zombie definitions, each zombie has a color! Can be randomized or parameterized based on user input.
*/ 

#include <iostream>
#include "termcolor.hpp"
#include "byers_zombie.h"
using namespace std;

//Constructor for randomly colored zombie
Zombie::Zombie(){
    int randNum = rand() % 5 + 1;
    if (randNum == 1){
        this->color = 'R';
    }
    else if(randNum == 2){
        this->color = 'Y';
    }
    else if(randNum == 3){
        this->color = 'G';
    }
    else if(randNum == 4){
        this->color = 'B';
    }
    else if(randNum == 5){
        this->color = 'M';
    }
    else if(randNum == 6){
        this->color = 'C';
    }

    //If the random number gen is bad
    else{
        this->color = '#';
    }
}

//Constructor for a zombie with the user's chosen color
Zombie::Zombie(char userColor){
    this->color = userColor;
}

//Zombie Destructor
Zombie::~Zombie(){
    delete this;
}

//Getters
char Zombie::getColor(){
    return this->color;
}

//Setters
void Zombie::setColor(char userColor){
    this->color = userColor;
}


//Operator overloading to properly print zombie colors, and compare two zombies!
bool Zombie::operator==(const Zombie* zomb){
    return this->color==zomb->color;
}

ostream& operator<<(ostream& os, Zombie* zomb){
    char color = zomb->getColor();
    if(color == 'R'){
      os<<termcolor::red<<"{"<<zomb->getColor()<<"} "<<termcolor::reset;
    }
    else if(color == 'Y'){
      os<<termcolor::yellow<<"{"<<zomb->getColor()<<"} "<<termcolor::reset;
    }
    else if(color == 'G'){
      os<<termcolor::green<<"{"<<zomb->getColor()<<"} "<<termcolor::reset;
    }
    else if(color == 'B'){
      os<<termcolor::blue<<"{"<<zomb->getColor()<<"} "<<termcolor::reset;
    }
    else if(color == 'M'){
      os<<termcolor::magenta<<"{"<<zomb->getColor()<<"} "<<termcolor::reset;
    }
    else if(color == 'C'){
      os<<termcolor::cyan<<"{"<<zomb->getColor()<<"} "<<termcolor::reset;
    }
    else{
        os<<"{"<<zomb->getColor()<<"} ";
    }
    
    return os;
}
