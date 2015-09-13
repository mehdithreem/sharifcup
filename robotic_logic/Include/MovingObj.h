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
#include "../Include/params.h"

using namespace std;

class MovingObj{
public:
	int direction;
	int radious;
	bool updated;
	geometry::Vector velocity;
	geometry::Vector COM;
	vector < geometry::Vector > coords;

	params::Color color;
	params::Shape shape;
	int regionID;
	MovingObj();

	void update(geometry::Vector _v , vector<geometry::Vector> _coords , int _d=0 );
	void updateConcave(geometry::Vector _v , vector<geometry::Vector> _coords ,int _d=0);
	double distWithCOM(geometry::Vector x, geometry::Vector y);

	void setColor(params::Color _color);
	void setShape(params::Shape _shape);
	void print();
};

#endif
