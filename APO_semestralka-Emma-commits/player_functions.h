#ifndef PLAYER_FUNCTIONS_H
#define PLAYER_FUNCTIONS_H

bool playerMove(GameBoard_t* GameBoard, int playerID, position_t* position, playerMove_enum playerMovement);
void setStartingPosition(GameBoard_t* gameboard, position_t* positionPlayer1, position_t* positionPlayer2);

#endif //PLAYER_FUNCTIONS_H