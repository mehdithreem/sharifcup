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

MovingObj::MovingObj(): velocity(Vector(0,0)) , COM(Vector(0,0)) {}

void MovingObj::update(Vector _v , vector<Vector> _coords)
{
	// reinit variables
	velocity = _v;
	coords.clear();
	COM = Vector(0,0);

	// update coordinates
	for(int i = 0; i < _coords.size(); i++){
		COM.x += _coords[i].x;
		COM.y += _coords[i].y;
		
		coords.push_back(_coords[i]);
	}

	COM = COM/_coords.size();

	// sortCoordsByPolar(coords ,COM);
}
