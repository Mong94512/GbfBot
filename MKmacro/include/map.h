#ifndef MAP_H
#define MAP_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>

class Map{
private:
    std::vector<COORD> pos;
    POINT cursor;
    int mapAmount = 0;

public:
    int MapAmount() {return mapAmount;}
    void getPos();
    void storePos();

};

#endif