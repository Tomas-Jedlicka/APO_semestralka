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

unsigned int COLORS[6] = {
    0x0000, //black
    0xf800, //red
    0x07c0, //green
    0x029f, //blue
    0xffe0, //yellow
    0xffff, //white
};
