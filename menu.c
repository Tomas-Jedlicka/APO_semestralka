#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "main.h"


bool checkColor(int *playerColor, int test){
    if(*playerColor < 1 || *playerColor > 5){
        return false;
    }
    if(test != 1){
        return false;
    }
    return true;
}

bool checkSpeed(int *speed, int test){
    if(*speed < 1 || *speed > 3){
        return false;
    }
    if(test != 1){
        return false;
    }
    return true;
}

bool menuPrint(int *player1Color, int *player2Color, int *speed){

    printf("Colors: 1-Red, 2-Green, 3-Blue, 4-Yellow, 5-White\n");
    printf("Player 1 choose your color: \n");
    int r = scanf("%d", &*player1Color);

    if(!checkColor(player1Color, r)){
        fprintf(stderr, "Wrong input for color\n");
        return false;
    }
    printf("Player 2 choose your color: \n");
    int q = scanf("%d", &*player2Color); 
    if(q!=1) return 1;
    while(player1Color == player2Color){
        printf("Choose different color than Player 1!\nPlayer 2 choose your color:\n");
        int q = scanf("%d", &*player2Color); 
        if(q!=1) return false;
    }
    
    if(!checkColor(player2Color, r)){
        fprintf(stderr, "Wrong input for color\n");
        return false;
    }

    printf("Speed: 1-Slow, 2-Medium, 3-Fast\n");
    printf("Choose speed: \n");
    int test = scanf("%d", &*speed);

    if(!checkSpeed(speed, test)){
        fprintf(stderr, "Wrong input for speed!\n");
        return false;
    }
    return true;
}


