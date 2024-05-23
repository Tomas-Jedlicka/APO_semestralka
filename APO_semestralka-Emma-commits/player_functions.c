#include <stdbool.h>
#include "main.h"
#include "player_functions.h"


static bool validMove(position_t* position)
{
    if (0 <= position->x
        && position->x < 96
        && 0 <= position->y
        && position->y < 64)
        return true;
    else
        return false;
}

bool playerMove(GameBoard_t* GameBoard, int playerID, position_t* position, playerMove_enum playerMovement) {

    switch (playerMovement) {
    case UP:
        position->y -= 1;
        if (!validMove(position) || GameBoard->array[position->y][position->x] != EMPTY) {
            return false;
        }
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
        }
    case DOWN:
        position->y += 1;
        if (!validMove(position) || GameBoard->array[position->y][position->x] != EMPTY)
            return false;
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
        }
    case LEFT:
        position->x -= 1;
        if (!validMove(position) || GameBoard->array[position->y][position->x] != EMPTY)
            return false;
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
        }

    case RIGHT:
        position->x += 1;
        if (!validMove(position) || GameBoard->array[position->y][position->x] != EMPTY)
            return false;
        else {
            GameBoard->array[position->y][position->x] = playerID;
            break;
        }
    }
    return true;
}

void setStartingPosition(GameBoard_t* gameboard, position_t* positionPlayer1, position_t* positionPlayer2)
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

