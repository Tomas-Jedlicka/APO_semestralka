#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//size of the board
#define ROWS 64
#define COLS 96

//player values on board
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

//board sturct
typedef struct rectangle_t{
  int rows;
  int cols;
} rectangle_t;

//player move directions
typedef enum playerMove_enum{
  LEFT,
  UP,
  RIGHT,
  DOWN
} playerMove_enum;

//player position
typedef struct position_t{
    int x;
    int y;
} position_t;

//board 
typedef struct GameBoard_t{
    int **array;
    rectangle_t size;
} GameBoard_t;


#endif //MAIN_H
