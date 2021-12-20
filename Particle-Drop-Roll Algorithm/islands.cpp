#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include "termcolor.hpp"


//Forward declarations
int** makeParticleMap(int width, int height, int windowX, int windowY, int winWidth, int winHeight, int numParticles, int maxLife);
bool moveExists(int** map, int width, int height, int x, int y);
int findMax(int** map, int width, int height);
void normalizeMap(int** map, int width, int height, int maxVal);
int* findMoves(int** map, int width, int height, int x, int y);
void obliterate2D(int** array, int row, int col);
void obliterate2D(char** array, int row, int col);
void print2D(int** arr, int width, int height);
void print2D(char** arr, int width, int height);
char** intToCharMap(int** intMap, int width, int height, int waterline);

using namespace std;

//Create the map of integers
int** makeParticleMap(int width, int height, int windowX, int windowY, int winWidth, int winHeight, int numParticles, int maxLife){
    //Seed Randomization
    srand(time(NULL));

    //MAP DEFINED map[Y][X]
    int** map;
    map = new int*[height];
    for(int row = 0; row < height; row++){
        map[row] = new int[width];
    }

    //Assign Default value of 0 to all
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            map[row][col] = 0;
        }
    }

    //Begin Drop-Roll-Generation
    //For each particle...
    for(int i = 0; i < numParticles; i++){
        //cout << "Starting sequence for partcile " << i << endl;
        int randX = rand() % (winWidth) + windowX;
        int randY = rand() % (winHeight) + windowY; 
        //For each life counter of the particle
        for(int particleLife = maxLife; particleLife > 0; particleLife--){
            map[randY][randX] = *(*(map + randY)+randX) + 1;
            //Check if a move exists before trying to make one
            if(moveExists(map, width, height, randX, randY)){
                //If there's a move, check which moves are valid
                int* moveArray = findMoves(map, width, height, randX, randY);
                
                //first index is number of valid moves, indexes containing the moves start at 1
                int moveIndex = (rand() % moveArray[0]) + 1;
                int selectedMove = *(moveArray + moveIndex);


                
                //Make the move based on the randomization
                //0  1  2
                //3  p  4
                //5  6  7
                if(selectedMove == 0){
                    randX -= 1;
                    randY -= 1;  
                }
                else if(selectedMove == 1){
                    randY -= 1;
                }
                else if(selectedMove == 2){
                    randY -= 1;
                    randX += 1;
                }
                else if(selectedMove == 3){
                    randX -= 1;
                }
                else if(selectedMove == 4){
                    randX += 1;
                }
                else if(selectedMove == 5){
                    randY += 1;
                    randX -= 1;
                }
                else if(selectedMove == 6){
                    randY += 1;
                }
                else if(selectedMove == 7){
                    randY += 1;
                    randX += 1;
                }

                delete[] moveArray;
            }
            //If there's no valid moves, no more particle life
            else{
                particleLife = 0;
            }
        }
    }
     
    return map;
}
//Check if a move for a particle[y][x] exists
bool moveExists(int** map, int width, int height, int x, int y){
    //Moves are checked with indexes as such (p is particle)
    //0  1  2
    //3  p  4
    //5  6  7

    //Checking the validity of Move 0
    if(!(y-1 < 0) && !(x-1 < 0)){
        if(*(*(map+(y-1))+(x-1)) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 1
    if(!(y-1 < 0)){
        if(*(*(map+(y-1))+x) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 2
    if(!(y-1 < 0) && !(x+1 > width-1)){
        if(*(*(map+(y-1))+(x+1)) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 3
    if(!(x-1 < 0)){
        if(*(*(map+y)+(x-1)) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 4
    if(!(x+1 > width-1)){
        if(*(*(map+y)+(x+1)) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 5
    if(!(x-1 < 0) && !(y+1 > height-1)){
        if(*(*(map+(y+1))+(x-1)) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 6
    if(!(y+1 > height-1)){
        if(*(*(map+(y+1))+(x)) <= *(*(map+ y)+x)){
            return true;
        }
    }
    //Checking the validity of Move 7
    if(!(x+1 > width-1) && !(y+1 > height-1)){
        if(*(*(map+(y+1))+(x+1)) <= *(*(map+ y)+x)){
            return true;
        }
    }

    return false;
}
//Function to find the maximum value in the grid
int findMax(int** map, int width, int height){
    int max = -1;
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            if(*(*(map + row)+col) > max){
                max = *(*(map + row)+col);
            }
        }
    }
    return max;
}
//Convert the values in the map to values from 0 to 255
void normalizeMap(int** map, int width, int height, int maxVal){
    float maxFloat = (float)maxVal;
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            float currentFloat = (float)*(*(map + row)+col);
            float floatResult = (currentFloat/maxFloat) * 255;
            int intResult = static_cast<int>(floatResult);
            map[row][col] = intResult;
        }
    }
}
//Function to find all valid moves and put them into an array
int* findMoves(int** map, int width, int height, int x, int y){
    int numValid = 0;
    int* validMoves = new int[8];

    for(int i = 0; i < 8; i++){
        validMoves[i] = -1;
    }
    //Checking the validity of Move 0
    if(!(y-1 < 0) && !(x-1 < 0)){
        if(map[y-1][x-1] <= map[y][x]){
            numValid++;
            validMoves[0] = 0;                      
        }
    }
    else{
        validMoves[0] = -1;
    }
    //Checking the validity of Move 1
    if(!(y-1 < 0)){
        if(map[y-1][x] <= map[y][x]){
            numValid++;
            validMoves[1] = 1;         
        }
    }
    else{
        validMoves[1] = -1;
    }
    //Checking the validity of Move 2
    if(!(y-1 < 0) && !(x+1 > width-1)){
        if(map[y-1][x+1] <= map[y][x]){
            numValid++;
            validMoves[2] = 2;
        }
    }
    else{
        validMoves[2] = -1;
    }
    //Checking the validity of Move 3
    if(!(x-1 < 0)){
        if(map[y][x-1] <= map[y][x]){
            numValid++;
            validMoves[3] = 3;
        }
    }
    else{
        validMoves[3] = -1;
    }
    //Checking the validity of Move 4
    if(!(x+1 > width-1)){
        if(map[y][x+1] <= map[y][x]){
            numValid++;
            validMoves[4] = 4;
        }
    }
    else{
        validMoves[4] = -1;
    }
    //Checking the validity of Move 5
    if(!(x-1 < 0) && !(y+1 > height-1)){
        if(map[y+1][x-1] <= map[y][x]){
            numValid++;
            validMoves[5] = 5;
        }
    }
    else validMoves[5] = -1;
    //Checking the validity of Move 6
    if(!(y+1 > height-1)){
        if(map[y+1][x] <= map[y][x]){
            numValid++;
            validMoves[6] = 6;
        }
    }
    else{
        validMoves[6] = -1;
    }
    //Checking the validity of Move 7
    if(!(x+1 > width-1) && !(y+1 > height-1)){
        if(map[y+1][x+1] <= map[y][x]){
            numValid++;
            validMoves[7] = 7;                               
        }
    }
    else{
        validMoves[7] = -1;
    }

    //Put all valid moves into an array
    //Index [0] represents the size of the array, for use of iteration later.
    int* finalValidMoves = new int[numValid + 1];
    finalValidMoves[0] = numValid;
    int mostRecentIndex = 1;
    //For each value in the validMoves array, put it into the finalValidMoves array, with index 0 being the number of valid moves for later randomization
    for(int i = 0; i < 8; i++){
        if(validMoves[i] != -1 && validMoves[i] <= 7 && validMoves[i] >= 0){
            finalValidMoves[mostRecentIndex] = validMoves[i];
            mostRecentIndex++;
        }
    }

    //Clear validMoves memory
    delete[] validMoves;
    return finalValidMoves;
}
//Function to free a 2D array from memory
void obliterate2D(int** array, int row, int col){
    for(int i = 0; i < row; i++){
        delete[] array[i];
    }
    delete[] array;
}
//Overload of obliterate2D for character arrays instead of ints
void obliterate2D(char** array, int row, int col){
    for(int i = 0; i < row; i++){
        delete[] array[i];
    }
    delete[] array;
}
//Prints the map to the console
void print2D(int** arr, int width, int height){
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            cout << *(*(arr + row)+col) << " ";
        }
        cout << endl;
    }
}
//Overload of print2D for character arrays instead of ints
void print2D(char** arr, int width, int height){
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            cout << *(*(arr + row)+col) << " ";
        }
        cout << endl;
    }
}
//Convert the integer map to its proper character symbols, and print in color
char** intToCharMap(int** intMap, int width, int height, int intWaterline){
    //Casting to floats for later use, and creating output file
    ofstream outFile("island.txt");
    float waterline = (float)intWaterline;
    float landzone = 255 - waterline;
    
    //Creation of 2D Character Map
    //defined charMap[Y][X]
    char** charMap = new char*[height];
    for(int row = 0; row < height; row++){
        charMap[row] = new char[width];
    }

    //Map each value in intMap to a character, and place in proper spot in charMap, print to cout and output file
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            int value = *(*(intMap + row)+col);
            //Deep Water
            if(value < (waterline/2)){
                charMap[row][col] = '#';
                cout << termcolor::blue << *(*(charMap + row)+col) << " ";
                outFile << termcolor::blue << *(*(charMap + row)+col) << " ";
            }
            //Shallow Water
            else if(value > (waterline/2) && value <= waterline){
                charMap[row][col] = '~';
                cout << termcolor::cyan << *(*(charMap + row)+col) << " ";
                outFile << termcolor::cyan << *(*(charMap + row)+col) << " ";
            }
            else if(value > waterline){
                //Coast or Beach
                if(value < (waterline + (landzone*.15))){
                    charMap[row][col] = '.';
                    cout << termcolor::yellow << *(*(charMap + row)+col) << " ";
                    outFile << termcolor::yellow << *(*(charMap + row)+col) << " ";
                }
                // Plains or Grass
                else if(value >= (waterline + (landzone*.15)) && value < (waterline + (landzone*.40))){
                    charMap[row][col] = '-';
                    cout << termcolor::bright_green << *(*(charMap + row)+col) << " ";
                    outFile << termcolor::bright_green << *(*(charMap + row)+col) << " ";
                }
                //Forests
                else if(value >= (waterline + (landzone*.40)) && value < (waterline + (landzone*.80))){
                    charMap[row][col] = '*';
                    cout << termcolor::green << *(*(charMap + row)+col) << " ";
                    outFile << termcolor::green << *(*(charMap + row)+col) << " ";
                }
                //Mountains
                else{
                    charMap[row][col] = '^';
                    cout << termcolor::white << *(*(charMap + row)+col) << " ";
                    outFile << termcolor::white << *(*(charMap + row)+col) << " ";
                }
            } 
        }
        cout << endl;
        outFile << endl;
    }
    outFile.close();
    return charMap;
}
int main(int argc, char** argv){

    //If user inputs more than one argument (invalid)
    if(argc > 1){
        cout << "Syntax: ./islands" << endl;
        return 0;
    }
    else{
    //Variable Declarations

    //Declarations for making sure input is valid
    bool validWidth, validHeight, validDropWindowX, validDropWindowY, validDropWindowWidth, validDropWindowHeight, validParticles, validMaxLife, validWaterline; 
    validWidth = validHeight = validDropWindowX = validDropWindowY = validDropWindowWidth = validDropWindowHeight = validParticles = validMaxLife = validWaterline = false;

    //Declarations for particle
    int gridWidth, gridHeight, dropWindowX, dropWindowY, dropWindowWidth, dropWindowHeight, particlesToDrop, maxLife, waterline;

    //Prompt user for variable inputs
    cout << "Welcome to island generator!\n" << endl;

    //While loops for each individual input to make sure they are all valid
    while(!validWidth){
        cout << "Enter grid width: ";
        cin >> gridWidth;
        if(gridWidth > 0){
            validWidth = true;
        }
        else{
            cout << "Please enter a number more than 0!" << endl << endl;
        }
    }
    while(!validHeight){
        cout << "Enter grid height: ";
        cin >> gridHeight;
        if(gridHeight > 0){
            validHeight = true;
        }
        else{
            cout << "Please enter a number more than 0!" << endl << endl;
        }
    }
    while(!validDropWindowX){
        cout << "Enter drop-window x-coordinate (0 - " << gridWidth << "): ";
        cin >> dropWindowX;
        if(dropWindowX > 0 && dropWindowX < gridWidth){
            validDropWindowX = true;
        }
        else{
            cout << "Please enter a number within the range provided!" << endl << endl;
        }
    }
    while(!validDropWindowY){
        cout << "Enter drop-window y-coordinate (0 - " << gridHeight << "): ";
        cin >> dropWindowY;
        if(dropWindowY > 0 && dropWindowY < gridHeight){
            validDropWindowY = true;
        }
        else{
            cout << "Please enter a number within the range provided!" << endl << endl;
        }
    }
    while(!validDropWindowWidth){
        cout << "Enter drop-window width (1 - " << gridWidth-dropWindowX << "): ";
        cin >> dropWindowWidth;
        if(dropWindowWidth >= 1 && dropWindowWidth <= gridWidth-dropWindowX){
            validDropWindowWidth = true;
        }
        else{
            cout << "Please enter a number within the range provided!" << endl << endl;
        }
    }
    while(!validDropWindowHeight){
        cout << "Enter drop-window height (1 - " << gridHeight-dropWindowY << "): ";
        cin >> dropWindowHeight;
        if(dropWindowHeight >= 1 && dropWindowHeight <= gridHeight-dropWindowY){
            validDropWindowHeight = true;
        }
        else{
            cout << "Please enter a number within the range provided!" << endl << endl;
        }
    }
    while(!validParticles){
        cout << "Enter number of particles to drop: ";
        cin >> particlesToDrop;
        if(particlesToDrop > 0){
            validParticles = true;
        }
        else{
            cout << "Please enter a number greater than 0!" << endl << endl;
        }
    }
    while(!validMaxLife){
        cout << "Enter max life of particles: ";
        cin >> maxLife;
        if(maxLife > 0){
            validMaxLife = true;
        }
        else{
            cout << "Please enter a number greater than 0!" << endl << endl;
        }
    }
    while(!validWaterline){
        cout << "Enter value for waterline (40-200): ";
        cin >> waterline;
        if(waterline >= 40 && waterline <= 200){
            validWaterline = true;
        }
        else{
            cout << "Please enter a number within range!" << endl;
        }
    }
        cout << "\n\n\nEND PROMPTS" << endl;
        
    //Create the map, find the max value, normalize it, then print its character version to cout and output file
    int** myMap = makeParticleMap(gridWidth, gridHeight, dropWindowX, dropWindowY, dropWindowWidth, dropWindowHeight, particlesToDrop, maxLife);
    int maxValue = findMax(myMap, gridWidth, gridHeight);
    normalizeMap(myMap, gridWidth, gridHeight, maxValue);
    char** myCharMap = intToCharMap(myMap, gridWidth, gridHeight, waterline);
    
    cout << "Map has been output to \"island.txt\"" << endl;

    //Delete dynamically allocated arrays
    obliterate2D(myMap, gridHeight, gridWidth);
    obliterate2D(myCharMap, gridHeight, gridWidth);

    return 0;
    }
}