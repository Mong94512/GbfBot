#ifndef BOT_H
#define BOT_H

#include<windows.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

using namespace std::chrono;

class Bot{
private:

    bool load;

    //Points
    std::vector<int> x;
    std::vector<int> y;

    //Points resetter
    std::vector<int> x1;
    std::vector<int> y1;

    //Set counter
    int set;
    int count = 1;

    //For data printing
    std::vector<int> sX;
    std::vector<int> sY;
    std::vector<int> time;

    //Captcha found
    bool found = false;

    //Click Delay
    int baseDelay;
    int attackDelay;
    int afterDelay;

    //Coord randomizer
    std::vector<int> xrange;
    std::vector<int> yrange;

public:
    //Accessor
    bool Load ();
    int X (int elem);
    int Y (int elem);
    int X1 (int elem);
    int Y1 (int elem);
    int Time (int elem);
    int Set ();
    int Count ();

    //Functions
    void getData();
    void getSet();
    void initCoord();
    void findCoord(int action);
    void findDelay(int action);
    void getTime(int timeTaken);
    void printData();
    int vectorSize();

};

#endif