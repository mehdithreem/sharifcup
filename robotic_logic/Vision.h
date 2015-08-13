#ifndef robotic_logic_Vision_h
#define robotic_logic_Vision_h

bool NewFrameIsReady();
void update(MovingObj& ourBot , MovingObj& enemyBot , vector<MovingObj>& obstacles);

#endif
