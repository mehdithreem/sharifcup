#ifndef robotic_logic_Vision_h
#define robotic_logic_Vision_h

#include "../Include/MovingObj.h"

//kolan not been coded ::DD
bool NewFrameIsReady();
void update(MovingObj& ourBot , MovingObj& enemyBot , vector<MovingObj>& obstacles);

#endif
