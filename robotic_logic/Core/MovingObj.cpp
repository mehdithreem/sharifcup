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

MovingObj::MovingObj(): velocity(Vector(0,1)) , COM(Vector(0,0)) {}

void MovingObj::update(Vector _v , vector<Vector> _coords)
{

//  	// reinit variables
//	velocity = _v;
//	coords.clear();
//	COM = Vector(0,0);
//  coords = geometry::convex_hull(_coords);
//	// update coordinates
//	for(int i = 0; i < coords.size(); i++){
//		COM= COM + coords[i];
//		//COM.y += coords[i].y;
//	//	coords.push_back(_coords[i]);
//	}
//  COM = COM/coords.size();
//  sortCoordsByPolar(coords , COM);


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
  
	sortCoordsByPolar(coords , COM);
}

void MovingObj::updateConcave(Vector _v , vector<Vector> _coords)
{
	// reinit variables
	velocity = _v;
	coords.clear();
	COM = Vector(0,0);

	// update coordinates
	for(int i = 0; i < _coords.size(); i++){
		COM = COM + _coords[i];

		coords.push_back(_coords[i]);
	}

	COM = COM/_coords.size();
  
	// sortCoordsByPolar(coords , COM);
}

void MovingObj::print()
{
	cout << "V:" << velocity << " C:" << COM << endl;
	cout << "Pts: ";
	for (geometry::Vector coordinate : coords)
		cout << coordinate << " ";
	cout << endl;
}
