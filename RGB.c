#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "mzapo_regs.h"


void RGB(int playerColor, unsigned char* mem_base){


    switch(playerColor){
        case(1):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x00FF0000;
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x00FF0000;
            break;
        case(2):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x0000FF00;
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x0000FF00;
            break;
        case(3):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x000000FF;
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x000000FF;
            break;
        case(4):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x00FFFF00;
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x00FFFF00;
            break;
        case(5):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x00FFFFFF;
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x00FFFFFF;
            break;
    }
}

void RGB1(int playerColor, unsigned char* mem_base){


    switch(playerColor){
        case(1):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x00FF0000;
            break;
        case(2):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x0000FF00;
            break;
        case(3):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x000000FF;
            break;
        case(4):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x00FFFF00;
            break;
        case(5):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0x00FFFFFF;
            break;
    }
}

void RGB2(int playerColor, unsigned char* mem_base){


    switch(playerColor){
        case(1):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x00FF0000;
            break;
        case(2):;
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x0000FF00;
            break;
        case(3):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x000000FF;
            break;
        case(4):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x00FFFF00;
            break;
        case(5):
            *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0x00FFFFFF;
            break;
    }
}

