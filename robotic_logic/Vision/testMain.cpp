//
//  main.cpp
//  RobotVision
//
//  Created by Ali on 6/20/1394 AP.
//  Copyright (c) 1394 Ali. All rights reserved.
//

#include <iostream>
#include "../Include/Vision.h"

int main(int argc, const char * argv[]) {
    Field field;
    RobotVision vision;
    vision.init();
    while (true) {
        vision.update(field);
        cout << "agent degree :" <<  field.agent.direction;
        cout << "first point :" <<  field.agent.coords[0].x << " " << field.agent.coords[0].y << endl;
        if(waitKey(33) == 27){
            break ;
        }
    }
}
