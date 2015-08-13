//
//  MovingObj.cpp
//  robotic_logic
//
//  Created by Nahal on 8/9/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//
#include <iostream>
#include "MovingObj.h"

using namespace std;
using namespace geometry;

MovingObj :: MovingObj(): velocity(Vector(0,0)) , gravityCenter(Vector(0,0)){}

MovingObj :: ~MovingObj(){
  cerr <<"MovingObj deleted !"<<endl;
}

void MovingObj :: update(Vector _v , vector<Vector > _coords)
{
    velocity = _v;
    gravityCenter = Vector(0,0);
    for(int i=0 ; i<_coords.size() ; i++){
        gravityCenter.x += _coords[i].x;
        gravityCenter.y += _coords[i].y;
        Vector polar = cart2polar(_coords[i]);
        pair< Vector , Vector> pairOfCartAndPolar = make_pair(_coords[i],polar);
        coords.push_back(pairOfCartAndPolar);
    }
    gravityCenter = gravityCenter/_coords.size();
}

void MovingObj :: sortCoordsByPolar(geometry::Vector newCenter){
  sort(coords.begin() ,coords.end() ,geometry::polarComparator);
}
