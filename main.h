typedef struct rectangle_t{
  int rows;
  int cols;
} rectangle_t;

typedef enum playerMove_enum{
  UP,
  DOWN,
  LEFT,
  RIGHT
} playerMove_enum;

typedef struct position_t{
    int x;
    int y;
} position_t;

typedef struct GameBoard_t{
    int **array;
    rectangle_t size;
} GameBoard_t;
