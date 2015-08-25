//
//  MovingObj.h
//  robotic_logic
//
//  Created by Nahal on 8/8/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//

#ifndef robotic_logic_MovingObj_h
#define robotic_logic_MovingObj_h

#include <vector>
#include <utility>
#include "../Include/geometry.h"
#include "../Include/clipper.h"

using namespace std;

class MovingObj{
public:
	geometry::Vector velocity;
	geometry::Vector COM;
	vector < geometry::Vector > coords;

	MovingObj();

	void update(geometry::Vector _v , vector<geometry::Vector> _coords);
	void updateConcave(geometry::Vector _v , vector<geometry::Vector> _coords);
	void print();
};

#endif
