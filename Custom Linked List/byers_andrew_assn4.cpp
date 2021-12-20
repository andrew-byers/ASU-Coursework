/*
Author: Andrew Byers
Date: 11/24/21
Description: Zombie Conga Line! Use a linked list and a zombie class to make a conga line of zombies and run a party where they move all around the linked list!
*/ 

#include <iostream>
#include <time.h>
#include "byers_list.h"
#include "byers_node.h"
#include "byers_zombie.h"
#include "termcolor.hpp"
using namespace std;

void engine(LinkedList<Zombie*>* list, Zombie* zomb){
    cout <<"(ENGINE!)"<< endl;
    list->addToFront(zomb);
}

void caboose(LinkedList<Zombie*>* list, Zombie* zomb){
    cout <<"(CABOOSE!)"<< endl;
    list->addToEnd(zomb);
}

void jumpInLine(LinkedList<Zombie*>* list, Zombie* zomb, int pos){
    cout <<"(JUMP IN LINE!)"<< endl;
    list->addAtIndex(zomb, pos);
}

void everyoneOut(LinkedList<Zombie*>* list, Zombie* zomb){
    cout <<"(EVERYONE OUT!)"<< endl;
    list->removeAllOf(zomb);
}

void youreDone(LinkedList<Zombie*>* list, Zombie* zomb){
    cout <<"(YOU'RE DONE!)"<< endl;
    list->removeTheFirst(zomb);
}

void brains(LinkedList<Zombie*>* list, Zombie* zomb){
    cout <<"(BRAINS!)"<< endl;
    Zombie* newOne = new Zombie(zomb->getColor());
    Zombie* newTwo = new Zombie(zomb->getColor());
    list->addToFront(zomb);
    list->addAtIndex(newOne, (list->length())/2);
    list->addToEnd(newTwo);
}

void rainbowBrains(LinkedList<Zombie*>* list, Zombie* zomb){
    cout <<"(RAINBOW BRAINS!)"<< endl;
    list->addToFront(zomb);
    list->addToEnd(new Zombie('R'));
    list->addToEnd(new Zombie('Y'));
    list->addToEnd(new Zombie('G'));
    list->addToEnd(new Zombie('B'));
    list->addToEnd(new Zombie('M'));
    list->addToEnd(new Zombie('C'));
}

int main(int argc, char** argv){
    //Seeding random and initializing variables for counts
    srand(time(NULL));
    int setupCount = 0;
    int numOfActions = rand() % 3 + 2;
    int desiredRounds;
    char runDesire;
    bool validRounds = false;
    bool wantsToRun = true;
    bool validDesireToRun = false;
    
    //Larger loop for if user wants to run it again later
    while(wantsToRun){
        int rounds = 1;
        int countTo5 = 1;

        //Input loop for rounds
        while(!validRounds){
            cout << "Please enter the amount of rounds you would like to run: ";
            cin >> desiredRounds;
            if(desiredRounds < 1){
                cout << "Please enter a number greater than 0!" << endl << endl;
            }
            else validRounds = true;
        }

        //Create linked list and first zombie! (random zombie)
        LinkedList<Zombie*>* myList = new LinkedList<Zombie*>();
        Zombie* firstZomb = new Zombie();
        
        //Setup - Rainbow Brains and a few random actions
        rainbowBrains(myList, firstZomb);
        while(setupCount <= numOfActions){
            int randAction = rand() % 6 + 1;
            //ENGINE!
            if(randAction == 1) engine(myList, firstZomb);
            //CABOOSE!
            else if(randAction == 2) caboose(myList, firstZomb);
            //JUMP IN THE LINE!!
            else if(randAction == 3) jumpInLine(myList, firstZomb, (rand() % 1 + myList->length())-1);
            //EVERYONE OUT!
            else if(randAction == 4) everyoneOut(myList, firstZomb);
            //YOU'RE DONE!
            else if(randAction == 5) youreDone(myList, firstZomb);
            //BRAINS!
            else if(randAction == 6) brains(myList, firstZomb);
            //RAINBOW BRAINS!
            else if(randAction == 7) rainbowBrains(myList, firstZomb);
            //Failsafe
            else cout << "BAD RNG!!!!" << endl;
            setupCount++;
        }
        //END setup

        //BEGIN THE CONGA BAYBEE 
        //
        //While you still have rounds to go
        while(rounds <= desiredRounds){
            //New round, new zombie
            Zombie* roundZombie = new Zombie();
            
            //Initial output
            cout << "Round: " << rounds << endl;
            cout << "The Zombie Party is still groovin, baby!" << endl;
            cout << "Size: " << myList->length() << " -> ";
            myList->printList();

            //If it's been 5 rounds, remove Head and Tail
            if(countTo5 == 5){
                cout << "5 rounds!! The front and back are gone!" << endl;
                myList->removeFromFront();
                myList->removeFromEnd();
                countTo5 = 1;
            }

            //Initiate the random action
            int randAction = rand() % 6 + 1;
            //ENGINE!
            if(randAction == 1){ 
                cout << roundZombie->getColor() << " zombie is hopping up front!  ";
                engine(myList, roundZombie); 
            }
            //CABOOSE!
            else if(randAction == 2) {
                cout << roundZombie->getColor() << " zombie is pulling up behind!";
                caboose(myList, roundZombie);
            }
            //JUMP IN THE LINE!!
            else if(randAction == 3) {
                cout << roundZombie->getColor() << " zombie hops into the thick of it!";
                jumpInLine(myList, roundZombie, (rand() % 1 + myList->length())-1);
            }
            //EVERYONE OUT!
            else if(randAction == 4) {
                cout << roundZombie->getColor() << " zombie makes everyone like him disappear!";
                everyoneOut(myList, roundZombie);
            }
            //YOU'RE DONE!
            else if(randAction == 5) {
                cout << roundZombie->getColor() << " zombie removes that familiar lookin fellow up front!";
                youreDone(myList, roundZombie);
            }
            //BRAINS!
            else if(randAction == 6) {
                cout << roundZombie->getColor() << " zombie brings some pals!";
                brains(myList, roundZombie);
            }
            //RAINBOW BRAINS!
            else if(randAction == 7) {
                cout << roundZombie->getColor() << " zombie is bringing some variety in!";
                rainbowBrains(myList, roundZombie);
            }
            //Failsafe
            else cout << "BAD RNG!!!!" << endl;

            cout << "The conga line is now: " << endl;
            myList->printList();
            cout << "*******************************************************************" << endl << endl;

            //If there's no head, there's no party
            if(myList->retrieveFront() == nullptr){
                cout << "The party is over :(" << endl;
            }
            rounds++;
            countTo5++;
        }
        //END THE ZOMBIE CONGA LINE

        cout <<"Rounds complete!" << endl << endl;
        validDesireToRun = false;

        //Ask the user if they want to go again
        while(!validDesireToRun){
            cout << "Would you like to continue? (y/n)" << endl;
            cin >> runDesire;
            if(runDesire == 'y'){
                wantsToRun = true;
                validDesireToRun = true;
                validRounds = false;
            }
            else if(runDesire == 'n'){
                wantsToRun = false;
                validDesireToRun = true;
                validRounds = false;
            }
            else{
                cout << "Please enter either y or n! (lowercase)" << endl << endl;
                validDesireToRun = false;
            }
        }   
    }
    //Exit larger loop


    return 0;
}