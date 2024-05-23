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
#include "knobs.h"
#include "menu.h"

#define ROWS 64
#define COLS 96

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

unsigned int COLORS [6] = {
    0x0000, //black
    0xf800, //red
    0x07c0, //green
    0x029f, //blue
    0xffe0, //yellow
    0xffff, //white
};

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
      && position->x < 96
      && 0 <= position->y
      && position->y < 64)
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
        if (!validMove(position) || GameBoard->array[position->y][position->x] != EMPTY ){
            return false;
        }  
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
        }  
    case DOWN:
        position->y += 1;
        if (!validMove(position) || GameBoard->array[position->y][position->x] != EMPTY )
            return false;
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
        }  
    case LEFT:
        position->x -= 1;
        if ( !validMove(position) || GameBoard->array[position->y][position->x] != EMPTY )
            return false;
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
            }

    case RIGHT:
        position->x += 1;
        if ( !validMove(position) || GameBoard->array[position->y][position->x] != EMPTY )
            return false;
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
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





//==========================================
//main
//==========================================


int main(int argc, char *argv[]) {

    int player1Color;
    int player2Color; 
    unsigned char *parlcd_mem_base;
    int i,j;
    unsigned int color;
    unsigned char *mem_base;
    int speed;

    
    if(!menuPrint(&player1Color, &player2Color, &speed)){
        return 1;
    }
    
    position_t positionPlayer1;
    position_t positionPlayer2;

    playerMove_enum playerMoving1 = RIGHT;
    playerMove_enum playerMoving2 = LEFT;

    //board init
    GameBoard_t GameBoard;
    GameBoard.size.rows = ROWS;
    GameBoard.size.cols = COLS;

    matrix_alloc(&GameBoard, GameBoard.size);
    
    setStartingPosition(&GameBoard,&positionPlayer1, &positionPlayer2);

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

    if (parlcd_mem_base == NULL)  exit(1);

    parlcd_hx8357_init(parlcd_mem_base);

    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);


    uint32_t rgb_knobs_value = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    
    if (mem_base == NULL)
        exit(1);
    
    int red;
    int blue;
    int last_red = ((rgb_knobs_value>>16)&0xff)/4%4;
    int last_blue = (rgb_knobs_value&0xff)/4%4;
    bool player1Won = false;
    bool player2Won = false;

    while (!player1Won && !player2Won) {

        last_red = red;
        last_blue = blue;
      
        rgb_knobs_value = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

        red = ((rgb_knobs_value>>16)&0xff)/4%4;
        blue = (rgb_knobs_value&0xff)/4%4;

        bool move1 = checkKnobs(last_red, red, &playerMoving1);  
        bool move2 = checkKnobs(last_blue, blue, &playerMoving2); 

        if(!move1){
            movePlayer(last_red, red, &playerMoving1);
        }

        if(!move2){
            movePlayer(last_blue, blue, &playerMoving2);
        }        

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (i = 0; i < 320 ; i++) {
            for (j = 0; j < 480 ; j++) {
                int ID = GameBoard.array[i/5][j/5];
                if(ID == EMPTY){
                    color = COLORS[0];
                }
                else if(ID == PLAYER1){
                    color = COLORS[player1Color];
                }else if(ID == PLAYER2){
                    color = COLORS[player2Color];
                }
                else{
                    return 100;
                }
                parlcd_write_data(parlcd_mem_base, color);
            }
        }

        if (!playerMove(&GameBoard, PLAYER1, &positionPlayer1, playerMoving1)) {

            player2Won = true; 

        }


        if (!playerMove(&GameBoard, PLAYER2, &positionPlayer2, playerMoving2)) {

            player1Won = true;
        }

        switch(speed){
            case 1:
                usleep(100000);
                break;
            case 2:
                usleep(50000);
                break;
            case 3:
                usleep(10000);
                break;
        }
    }

    if(player1Won && player2Won){
        printf("DRAW!\n");
        return 0;
    }
    if (player1Won) {
        printf("Player 1 won!\n");
    } else if (player2Won) {
        printf("Player 2 won!\n");

    }
 
    return 0;
}


