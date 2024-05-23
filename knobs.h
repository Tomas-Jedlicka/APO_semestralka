#ifndef KNOBS_H
#define KNOBS_H

#include <stdbool.h>

//checking if knobs are crossing from 3 to 0 in direction enum
bool checkKnobs(int last_value, int value, playerMove_enum *playerMoving);

//decides how to move player based on knob value
void movePlayer(int lastValue, int value, playerMove_enum *playerMoving);


#endif // KNOBS_H