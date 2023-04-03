#include "bot.h"
#include "detector.h"

//Accessor
bool Bot::Load() {return load;}
int Bot::X (int elem) {return x[elem];}
int Bot::Y (int elem) {return y[elem];}
int Bot::X1 (int elem) {return x1[elem];}
int Bot::Y1 (int elem) {return y1[elem];}
int Bot::Time (int elem) {return time[elem];}
int Bot::Set () {return set;}
int Bot::Count () {return count;}

//Functions
void Bot::getData(){

    int tempX, tempY;
    std::string dummy;
    int count = 0;

    //Cursor Position, Delay values, Coord randomizer values
    std::ifstream infile ("../data/info.txt");

    if(infile.is_open()){

        for(int line = 1; line <= 19; line++){

            if(line >=2 && line <= 6){

                infile>>tempX>>tempY;
                x.push_back(tempX);
                y.push_back(tempY);

            }
            if(line == 12){
                infile>>baseDelay>>attackDelay>>afterDelay;
            }
            if(line >= 15 && line <= 19){
                infile>>tempX>>tempY;
                xrange.push_back(tempX);
                yrange.push_back(tempY);
            }

            getline(infile, dummy);

        }
        infile.close();


        for(int i = 0; i<x.size(); i++){
            x1.push_back(x[i]);
            y1.push_back(y[i]);
        }

        load = true;
    }
    else{
        load = false;
    }
}

void Bot::getSet(){
    //Ask user no. of set
    std::cout<<"Enter no. of set: ";
    std::cin>>set;
}

void Bot::initCoord(){
    //Cursor Pos initializer
    for(int i = 0; i<x.size(); i++){
        x[i] = x1[i];
        y[i] = y1[i];
    }
}

void Bot::findCoord(int action){
    int xrand, yrand, roll;

    if(action == 0 || action == 4){
        xrand = rand() % xrange[0];
        yrand = rand() % yrange[0];
    }
    else if(action == 1){
        xrand = rand() % xrange[1];
        yrand = rand() % yrange[1];
    }
    else if(action == 2){
        xrand = rand() % xrange[2];
        yrand = rand() % yrange[2];
    }
    else if(action == 3){
        xrand = rand() % xrange[3];
        yrand = rand() % yrange[3];
    }

    roll = rand() % 2;
    if(roll == 0) x[action] = x[action] + xrand;
    else x[action] = x[action] - xrand;

    roll = rand() % 2;
    if(roll == 0) y[action] = y[action] + yrand;
    else y[action] = y[action] - yrand;

    sX.push_back(x[action]);
    sY.push_back(y[action]);

    SetCursorPos(x[action], y[action]);
}

void Bot::findDelay(int action){
    int addDelay;

    if(action == 3){
        addDelay = rand() % 200;
        Sleep(attackDelay + addDelay);
    }
    else{
        addDelay = rand() % 200;
        Sleep(baseDelay + addDelay);
    }
    
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    addDelay = rand() % 100;
    Sleep(addDelay);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    
    addDelay = rand() % 200;
    Sleep(afterDelay + addDelay);
}

void Bot::printData(){

    std::cout<<"Set "<<count<<" : \n";

    std::cout<<"X: ";
    for(int i = 0; i<sX.size(); i++){
        std::cout<<sX[i]<<" ";
    }
    std::cout<<"\nY: ";
    for(int i = 0; i<sY.size(); i++){
        std::cout<<sY[i]<<" ";
    }
    std::cout<<"\nTime: ";
    for(int i = 0; i<time.size(); i++){
        std::cout<<time[i]<<"ms ";
    }
    std::cout<<"\n\n";
    sX.clear();
    sY.clear();
    time.clear();
    count++;
    Sleep(1000);
}

void Bot::getTime(int timeTaken){
    time.push_back(timeTaken);
}

int Bot::vectorSize(){
    return x.size();
}