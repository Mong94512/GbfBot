#include "map.h"

void Map::getPos(){
    system("cls");
    std::cout<<"Mapping start.....\n";

    while(true){
        if(GetAsyncKeyState(0x52)){
            GetCursorPos(&cursor);
            COORD newCoord = { static_cast<SHORT>(cursor.x), static_cast<SHORT>(cursor.y) };
            pos.push_back(newCoord);
            mapAmount++;
            std::cout<<"Pos"<<mapAmount<<" mapped\n";
            Sleep(1000);
        }
        else if(GetAsyncKeyState(VK_ESCAPE) || mapAmount == 5){
            break;
        }
    }
    //Print mapped coordinates
    std::cout<<"\nRecorded pos: \n";
    for(int i = 0; i<pos.size(); i++){
        std::cout<<"Pos"<<i+1<<": "<<pos[i].X<<", "<<pos[i].Y<<"\n";
    }
}

void Map::storePos(){
    std::string dummy;
    int line = 1;
    int elem = 0;

    std::ifstream infile ("../data/info.txt");
    std::ofstream outfile ("../data/temp.txt");

    while(std::getline(infile, dummy)){
        if(line > 1 && line <= 6){
            outfile<<pos[elem].X<<" "<<pos[elem].Y<<'\n';
            elem++;
        }
        else{
            outfile<<dummy<<'\n';
        }

        line++;
    }

    infile.close();
    outfile.close();

    std::remove("../data/info.txt");
    std::rename("../data/temp.txt", "../data/info.txt");

    std::cout<<'\n';
    
    system("pause");
}

