#ifndef _FIELD_
#define _FIELD_

#include <vector>
#include <utility>
#include "../Include/geometry.h"
#include "../Include/MovingObj.h"
#include "../Include/Region.h"
#include "../Include/ShortestPath.h"
#include "../Include/Graph.h"
using namespace std;

class Field {
public:
	MovingObj rival, agent;
	vector<MovingObj> obstacles;

	vector<Region> regions;
	Field();
	
	pair<geometry::Vector,geometry::Vector> bestTarget(params::Color& targetColor, bool& done);
};

#endif
