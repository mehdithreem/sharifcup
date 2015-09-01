#ifndef robotic_logic_geometry_h
#define robotic_logic_geometry_h

#include<iostream>
#include<cmath>
#include<vector>
#include "../Include/geometry.h"
using namespace std;

//using namespace geometry;


void talkToSetare(int velocity , int angle ,int rotation);

void moveFree(vector<geometry::Vector> path , geomrtey::Vector vel);
void moveWithObs(vector< geometry::Vector > path , geometry::Vector vel);

#endif


