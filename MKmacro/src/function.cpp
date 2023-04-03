#include "function.h"
#include "bot.h"
#include "map.h"
#include "detector.h"

char getChoice(){
    char choice;
    std::cout<<"1. Botting 2. Mapping 3. Quit\n";
    std::cout<<"Choice: ";
    std::cin>>choice;

    return choice;
}

int ActivateBot(){
    srand(time(0));

    Bot bot;
    Detector captcha;

    bot.getData();
    captcha.getData();

    if(bot.Load() == true && captcha.Load() == true){

        bot.getSet();

        while(bot.Count() <= bot.Set()){

            bot.initCoord();

            for(int i = 0; i < bot.vectorSize(); i++){

                auto start = high_resolution_clock::now();

                if(i == 1){

                    captcha.getImages();
                    if(captcha.findCaptcha()){
                        std::thread sound(Alarm);
                        captcha.printResult();
                        sound.join();
                        return -1;
                    }
                }
                
                bot.findCoord(i);
                bot.findDelay(i);
                
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);

                bot.getTime(duration.count());
            }

            bot.printData();
        }
        
        std::cin.ignore(1);
        std::cin.get();
    }

    return 0;
}

void ActivateMapper(){
    Map map;

    map.getPos();
    if(map.MapAmount() == 5){
        map.storePos();
    }

}

void Alarm(){
    PlaySound(TEXT("../data/alarm.wav"), NULL, SND_FILENAME);
}