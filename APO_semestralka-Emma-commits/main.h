#ifndef MAIN_H
#define MAIN_H

#define ROWS 64
#define COLS 96

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

typedef struct rectangle_t{
  int rows;
  int cols;
} rectangle_t;

typedef enum playerMove_enum{
  LEFT,
  UP,
  RIGHT,
  DOWN
} playerMove_enum;

typedef struct position_t{
    int x;
    int y;
} position_t;

typedef struct GameBoard_t{
    int **array;
    rectangle_t size;
} GameBoard_t;


#endif //MAIN_H
