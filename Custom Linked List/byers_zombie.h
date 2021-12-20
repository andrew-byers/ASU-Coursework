/*
Author: Andrew Byers
Date: 11/24/21
Description: Zombie header, declarations
*/ 

#pragma once
#include <iostream>
using namespace std;

class Zombie{
    protected:
        char color;
    public:
        Zombie();
        Zombie(char userColor);
        ~Zombie();
        char getColor();
        void setColor(char userColor);
        bool operator==(const Zombie*);
        friend ostream& operator<<(ostream& os, Zombie* zomb);
};


