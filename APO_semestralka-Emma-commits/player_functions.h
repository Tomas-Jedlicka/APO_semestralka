#ifndef PLAYER_FUNCTIONS_H
#define PLAYER_FUNCTIONS_H

//moving player on board based on arguments input (posiiton and direction)
bool playerMove(GameBoard_t* GameBoard, int playerID, position_t* position, playerMove_enum playerMovement);

//sett starting position for player
void setStartingPosition(GameBoard_t* gameboard, position_t* positionPlayer1, position_t* positionPlayer2);

#endif //PLAYER_FUNCTIONS_H