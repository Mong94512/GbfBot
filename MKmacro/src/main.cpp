
#include "function.h"

int main(){

    while(true){
        
        switch(getChoice()){
            case '1': ActivateBot(); break;
            case '2': ActivateMapper(); break;
            case '3': return -1;
            default: break;
        }
        system("cls");
    }

    return 0;
}
