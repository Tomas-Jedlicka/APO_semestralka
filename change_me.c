#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "main.h"

#include <stdbool.h>

#define ROWS 96
#define COLS 64

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

int GameBoard[ROWS][COLS];

size_t matrix_array_length(const rectangle_t size)
{
    return size.cols * size.rows;
}

void matrix_alloc(GameBoard_t *matrix, const rectangle_t size)
{
    size_t sizeInBytes = sizeof(GameBoard_t) * matrix_array_length(size);
    matrix->array = (int *)malloc(sizeInBytes);
    if (matrix->array != NULL)
    {
        memset(matrix->array, 0, sizeInBytes);
        matrix->size = size;
    }
}

bool matrix_init(GameBoard_t *matrix, const rectangle_t size)
{
    memset(matrix, 0, sizeof(GameBoard_t));
    if (matrix_array_length(size) > 0)
    {
        matrix_alloc(matrix, size);
        return true;
    }
    else
    {
        return false;
    }
}

bool playerMove(int playerID, position_t position){

  playerMove_enum playerMove;

  switch (playerMove) {
    case UP:
    if (GameBoard [position.x - 1][position.y] != EMPTY)
      return false;
    else {
      GameBoard[position.x - 1][position.y] = playerID;
      break;
    }  
    case DOWN:
      if (GameBoard[position.x + 1][position.y] != EMPTY)
        return false;
      else {
        GameBoard[position.x + 1][position.y] = playerID;
        break;
      }  
    case LEFT:
      if (GameBoard[position.x][position.y - 1] != EMPTY)
        return false;
      else {
        GameBoard[position.x][position.y - 1] = playerID;
        break;
      }
    case RIGHT:
    if (GameBoard[position.x][position.y + 1] != EMPTY)
      return false;
    else {
      GameBoard[position.x][position.y + 1] = playerID;  
      break;
    }     
  }
  return true; 
}

bool makeContact(int player1, int player2, position_t position1, position_t position2){
  if (!playerMove(player1, position1) || !playerMove(player2, position2))
    return false;
  else
    return true;
}


int main(int argc, char *argv[]) {

  position_t positionPlayer1;
  position_t positionPlayer2;
  
  while(!makeContact(PLAYER1, PLAYER2, positionPlayer1, positionPlayer2))
  {
    //TO-DO -> whole game....
  }
 
  return 0;
}
