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
#include "player_functions.h"
#include "array_functions.h"
#include "RGB.h"
#include "printWinner.h"


unsigned int COLORS[6] = {
    0x0000, //black
    0xf800, //red
    0x07c0, //green
    0x029f, //blue
    0xffe0, //yellow
    0xffff, //white
};

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

    if (mem_base == NULL)
        exit(1);

    RGB1(player1Color, mem_base);
    RGB2(player2Color, mem_base);

    uint32_t rgb_knobs_value = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    
    int red;
    int blue;
    int last_red = ((rgb_knobs_value>>16)&0xff)/4%4;
    int last_blue = (rgb_knobs_value&0xff)/4%4;
    bool player1Won = false;
    bool player2Won = false;
    bool notFirstRound = false;

    while (!player1Won && !player2Won) {
        
        if(notFirstRound){
            last_red = red;
            last_blue = blue;
        }   
      
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

        notFirstRound = true;
    }

    if(player1Won && player2Won){
        printf("DRAW!\n");
        printDraw(parlcd_mem_base);
    }
    if (player1Won) {
        printf("Player 1 won!\n");
        printWinner1(parlcd_mem_base);
        RGB(player1Color, mem_base);
    } else if (player2Won) {
        printf("Player 2 won!\n");
        printWinner2(parlcd_mem_base);
        RGB(player2Color, mem_base);
    }

    return 0;
}


