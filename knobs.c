#include <stdbool.h>
#include "main.h"

bool checkKnobs(int last_value, int value, playerMove_enum *playerMoving){

    if(last_value == 0 && value == 3){
        if(*playerMoving != DOWN){
                *playerMoving += 1;
            }
            else{
                *playerMoving = LEFT;
            }
        return true;
    }
    
    if(last_value == 3 && value == 0){
        if(*playerMoving != LEFT){
                *playerMoving -= 1;
            }
            else{
                *playerMoving = DOWN;
            }
        return true;
    }
  
    return false;
}

void movePlayer(int lastValue, int value, playerMove_enum *playerMoving){
    if(lastValue < value){
        if(*playerMoving != DOWN){
            *playerMoving += 1;
        }
        else{
            *playerMoving = LEFT;
        }
    }

    if(lastValue > value){
        if(*playerMoving != LEFT){
            *playerMoving -= 1;
        }
        else{
            *playerMoving = DOWN;
        }
    }
}