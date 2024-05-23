#ifndef MENU_H
#define MENU_H

//printg menu to terminal
bool menuPrint(int *player1Color, int *player2Color, int *speed);

//taking color from terminal input and checking if it's bounds
bool checkColor(int playerColor, int test);

//taking speed from terminal input and checking if it's in bounds 
bool checkSpeed(int speed, int test);


#endif // MENU_H