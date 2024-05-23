#ifndef RGB_H
#define RGB_H

//setting up diods for winner in the end (both one color)
void RGB(int playerColor, unsigned char* mem_base);

//setting up diod color for player one (left diod)
void RGB1(int playerColor, unsigned char* mem_base);

//setting up diod color for player two (riht diod)
void RGB2(int playerColor, unsigned char* mem_base);

#endif //RGB_H