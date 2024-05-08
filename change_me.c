#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "main.h"

#define ROWS 64
#define COLS 96

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

//==========================================
//array functions
//==========================================

size_t matrix_array_length(const rectangle_t size)
{
    return size.cols * size.rows;
}

void matrix_alloc(GameBoard_t *matrix, const rectangle_t size)
{

    matrix->array = malloc(size.rows * sizeof(int *));
    if (matrix->array != NULL)
    {
        for (int i = 0; i < size.rows; i++)
        {
            matrix->array[i] = malloc(size.cols * sizeof(int));
            if (matrix->array[i] == NULL)
            {
                printf("Not ok");
            }
        }
        for (int i = 0; i < size.rows; i++)
        {
            for (int j = 0; j < size.cols; j++)
            {
                matrix->array[i][j] = EMPTY;
            }
        }

        matrix->size = size;
        printf("All good\n");
    }

}



bool validMove(position_t *position)
{
  if (0 <= position->x 
      && position->x  < 97 
      && 0 <= position->y 
      && position->y < 65)
    return true;
  else
   return false;
}

//==========================================
//player funnctions
//==========================================

bool playerMove(GameBoard_t *GameBoard, int playerID, position_t *position, playerMove_enum playerMovement){

  switch (playerMovement) {
    case UP:
        position->y -= 1;
        if (GameBoard->array[position->x][position->y] != EMPTY){
            return false;
        }  
        else {
        if (validMove(position))
        {
            GameBoard->array[position->x][position->y] = playerID;
            break;
        }
        else 
            {
            return false;
            }
        }  
    case DOWN:
        position->y += 1;
        if (GameBoard->array[position->x][position->y] != EMPTY)
            return false;
        else {
            if (validMove(position))
            {
            GameBoard->array[position->x][position->y] = playerID;
            break;
            }
            else 
            return false;
        }  
    case LEFT:
        position->x -= 1;
        if (GameBoard->array[position->x][position->y] != EMPTY)
            return false;
        else {
            if (validMove(position))
            {
            GameBoard->array[position->x][position->y] = playerID;
            break;
            }
            else 
            return false;
        }  
    case RIGHT:
        position->x += 1;
        if (GameBoard->array[position->x][position->y] != EMPTY)
        return false;
        else {
            if (validMove(position))
            {
            GameBoard->array[position->x][position->y] = playerID;
            break;
            }
            else 
            return false;
        }     
    }
    return true; 
  }




void setStartingPosition(GameBoard_t *gameboard,position_t *positionPlayer1, position_t *positionPlayer2)
{
  //player 1
  positionPlayer1->x = 15;
  positionPlayer1->y = 32;
  gameboard->array[positionPlayer1->y][positionPlayer1->x] = PLAYER1;

  //player 2
  positionPlayer2->x = 80;
  positionPlayer2->y = 32;
    gameboard->array[positionPlayer2->y][positionPlayer2->x] = PLAYER2;


}

bool checkColor(int playerColor, int test){
    if(playerColor < 1 || playerColor > 5){
        return false;
    }
    if(test != 1){
        return false;
    }
    return true;
}

bool checkSpeed(int speed, int test){
    if(speed < 1 || speed > 3){
        return false;
    }
    if(test != 1){
        return false;
    }
    return true;
}




//==========================================
//main
//==========================================

int main(int argc, char *argv[]) {

    int player1Color;
    int player2Color; 

    printf("Colors: 1-Red, 2-Green, 3-Blue, 4-Yellow, 5-White\n");
    printf("Player 1 choose your color: \n");
    int r = scanf("%d", &player1Color);

    if(!checkColor(player1Color, r)){
        fprintf(stderr, "Wrong input for color\n");
        return 1;
    }
    printf("Player 2 choose your color: \n");
    int q = scanf("%d", &player2Color); 
    while(player1Color == player2Color){
        printf("Choose different color than Player 1!\nPlayer 2 choose your color:\n");
        int q = scanf("%d", &player2Color); 
    }
    if(!checkColor(player2Color, r)){
        fprintf(stderr, "Wrong input for color\n");
        return 1;
    };


    int speed;
    printf("Speed: 1-Slow, 2-Medium, 3-Fast\n");
    printf("Choose speed: \n");
    int test = scanf("%d", &speed);
    if(!checkSpeed(speed, test)){
        fprintf(stderr, "Wrong input for speed!\n");
        return 1;
    }
    
    position_t positionPlayer1;
    position_t positionPlayer2;

    playerMove_enum playerMoving1 = UP;
    playerMove_enum playerMoving2 = DOWN;

    //board init
    GameBoard_t GameBoard;
    GameBoard.size.rows = ROWS;
    GameBoard.size.cols = COLS;

    matrix_alloc(&GameBoard, GameBoard.size);
    
    setStartingPosition(&GameBoard,&positionPlayer1, &positionPlayer2);

    
    bool player1Won = false;
    bool player2Won = false;
    int counter = 0;

    for(int i = 0; i < ROWS; i++){
            for(int j = 0; j < COLS; j ++){
                printf("%d", GameBoard.array[i][j]);
            }
            printf("\n");    
        }
        printf("\n\n");

    while (!player1Won && !player2Won) {
        printf("counter = %d\n", counter);

        if (!playerMove(&GameBoard, PLAYER1, &positionPlayer1, playerMoving1)) {

            player2Won = true; 
            break;
        }


        if (!playerMove(&GameBoard, PLAYER2, &positionPlayer2, playerMoving2)) {

            player1Won = true;
            break;
        }
 
        counter += 1;
        sleep(1);
        for(int i = 0; i < ROWS; i++){
            for(int j = 0; j < COLS; j ++){
                printf("%d", GameBoard.array[i][j]);
            }
            printf("\n");    
        }
        printf("\n\n");
    }

    if (player1Won) {
        printf("Player 1 won!\n");
    } else if (player2Won) {
        printf("Player 2 won!\n");

    }
 
    return 0;
}
