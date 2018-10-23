//
//  MovingObj.cpp
//  robotic_logic
//
//  Created by Nahal on 8/9/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//

#include <iostream>
#include "../Include/MovingObj.h"

using namespace std;
using namespace geometry;

MovingObj::MovingObj(): velocity(Vector(0,0)) , COM(Vector(0,0)) , direction(0), updated(false), speed(0) {}

void MovingObj::update(Vector _v  , vector<Vector> _coords, int _d)
{
	// velocity = _v;
	coords.clear();
	direction = _d;
	COM = Vector(0,0);
	for(int i = 0; i < _coords.size(); i++){
		COM.x += _coords[i].x;
		COM.y += _coords[i].y;

		coords.push_back(_coords[i]);
	}

	COM = COM/_coords.size();
  
	sortCoordsByPolar(coords , COM);

	if (coords.size() > 0) radious = (COM - coords[0]).size();
	else radious = 0;

	updated = true;

	return;
}

void MovingObj::updateConcave(Vector _v , vector<Vector> _coords ,int _d)
{
	// velocity = _v;
	coords.clear();
	direction = _d;
	COM = Vector(0,0);

	for(int i = 0; i < _coords.size(); i++){
		COM = COM + _coords[i];

		coords.push_back(_coords[i]);
	}
	COM = geometry::Vector(0,0);
	if (coords.size() > 0){ 
		radious = (COM - coords[0]).size();
		COM = COM/coords.size();
	}
	else radious = 0;

	updated = true;

	return;
}


void MovingObj::setColor(params::Color _color) {
	color = _color;
}
void MovingObj::setShape(params::Shape _shape) {
	shape = _shape;
}

double MovingObj::distWithCOM(geometry::Vector x, geometry::Vector y) {
	int a = (y.y - x.y) / (y.x - x.x);
	double dis = a*(COM.x-y.x) - (COM.y-y.x);
	dis = dis / (sqrt(a*a+1));

	return dis;	
}

void MovingObj::print()
{
	cout << "V:" << velocity << " C:" << COM << endl;
	cout << "Pts: ";
	for (geometry::Vector coordinate : coords)
		cout << coordinate << " ";
	cout << endl;
}
