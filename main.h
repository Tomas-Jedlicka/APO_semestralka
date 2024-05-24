/***********************************************************************************************
 * This is the source code of a game based on movie from 1984 named Tron.
 * ============================================================================================= 
 * 
 * Hardware:
 *  - MICROZED EVALUATION KIT
 *  - CPU -> Dual ARM® Cortex™-A9 MPCore™ @ 866 MHz
 *  - RAM -> 2x L1 32 kB data +32 kB instruction, L2 512 KB
 *  - Operation system -> GNU/Linux
 *      - GNU LIBC (libc6) 2.28-10
 *      - Jádro Linux 4.19.59-rt22-00005-gedf9096397ae src
 *      - Distribuce: Debian 10 Buster
 * 
 * More information about hardware:
 * -> https://www.avnet.com/wps/portal/us/products/avnet-boards/avnet-board-families/microzed/
 * -> https://gitlab.com/pikron/projects/mz_apo/microzed_apo 
 * 
 * Compilation:
 *  - gcc (arm-linux-gnueabihf-gcc)
 *  - binary package needed (Debian/ubuntu => "crossbuild-essential-armhf")
 *  - u need to build it first with make file
 *  - only need to change IP in the make file with an adress of the board
 *  - than run the binary with command "make run" on the board's terminal window
 * 
*************************************************************************************************/

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