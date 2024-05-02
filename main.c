#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
 
//#include "mzapo_parlcd.h"
//#include "mzapo_phys.h"
//#include "mzapo_regs.h"
//#include "font_types.h"
#include "main.h"

#define ROWS 96
#define COLS 64

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
    size_t sizeInBytes = sizeof(GameBoard_t) * matrix_array_length(size);
    matrix->array = malloc(sizeInBytes);
    if (matrix->array != NULL)
    {
        memset(matrix->array, 0, sizeInBytes);
        matrix->size = size;
        printf("point matrix");
    }
    else {
        printf("point null array");
    }
}

bool matrix_init(GameBoard_t *matrix, const rectangle_t size)
{
    memset(matrix, 0, sizeof(GameBoard_t));
    printf("point memset");
    if (matrix_array_length(size) > 0)
    {
        matrix_alloc(matrix, size);
        printf("point init");
        return true;
    }
    else
    {
        return false;
    }
}

bool validMove(position_t *position, int x, int y)
{
  if (0 <= position->x + x 
      && position->x + x < 97 
      && 0 <= position->y + y
      && position->y + y < 65)
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
    if (GameBoard->array[position->x][position->y - 1] != EMPTY){
        printf("a");
      return false;
    }  
    else {
      if (validMove(position, 0, -1))
      {
        GameBoard->array[position->x][position->y - 1] = playerID;
        break;
      }
      else 
        {
        printf("b");
        return false;
        }
    }  
    case DOWN:
      if (GameBoard->array[position->x][position->y + 1] != EMPTY)
        return false;
      else {
        if (validMove(position, 0, 1))
        {
          GameBoard->array[position->x][position->y + 1] = playerID;
          break;
        }
        else 
          return false;
      }  
    case LEFT:
      if (GameBoard->array[position->x - 1][position->y] != EMPTY)
        return false;
      else {
        if (validMove(position, -1, 0))
        {
          GameBoard->array[position->x - 1][position->y] = playerID;
          break;
        }
        else 
          return false;
      }  
    case RIGHT:
    if (GameBoard->array[position->x + 1][position->y] != EMPTY)
      return false;
    else {
        if (validMove(position, 1, 0))
        {
          GameBoard->array[position->x + 1][position->y] = playerID;
          break;
        }
        else 
          return false;
      }     
  }
  return true; 
}

bool makeContact(GameBoard_t *GameBoard, int player1, int player2, position_t *position1, position_t *position2, playerMove_enum playerMoving1, playerMove_enum playerMoving2){
  if (!playerMove(GameBoard, player1, position1, playerMoving1) || !playerMove(GameBoard, player2, position2, playerMoving2))
    return false;
  else
    return true;
}

void setStartingPosition(position_t *positionPlayer1, position_t *positionPlayer2)
{
  //player 1
  positionPlayer1->x = 15;
  positionPlayer1->y = 32;

  //player 2
  positionPlayer2->x = 80;
  positionPlayer2->y = 32;

}


//==========================================
//main
//==========================================

int main(int argc, char *argv[]) {

    sleep(5);
    printf("point -1");
    sleep(3);

    position_t positionPlayer1;
    position_t positionPlayer2;

    playerMove_enum playerMoving1 = UP;
    playerMove_enum playerMoving2 = DOWN;

    //board init
    GameBoard_t GameBoard;
    GameBoard.size.rows = ROWS;
    GameBoard.size.cols = COLS;

    if (!matrix_init(&GameBoard, GameBoard.size))
    {
        printf("pole not ok\n");
        return EXIT_FAILURE;
    }

    printf("point 0");

    setStartingPosition(&positionPlayer1, &positionPlayer2);
    printf("point 1");
    
    while(!makeContact(&GameBoard, PLAYER1, PLAYER2, &positionPlayer1, &positionPlayer2, playerMoving1, playerMoving2))
    {
        if (!playerMove(&GameBoard, PLAYER1, &positionPlayer1, playerMoving1))
        {
        //game over screen - player 2 won
        printf("player 2 won haha xDDD\n");
        break;
        }

        if (!playerMove(&GameBoard, PLAYER2, &positionPlayer2, playerMoving2))
        {
        //game over screen - player 1 won
        printf("player 1 won haha xDDD\n");
        break;
        }
        printf("ok");
        usleep(100000);
        //TO-DO -> whole game....
    }
 
  return 0;
}
