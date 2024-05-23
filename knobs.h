#ifndef KNOBS_H
#define KNOBS_H

#include <stdbool.h>

bool checkKnobs(int last_value, int value, playerMove_enum *playerMoving);
void movePlayer(int lastValue, int value, playerMove_enum *playerMoving);


#endif // KNOBS_H