#ifndef _FIELD_
#define _FIELD_

#include <vector>
#include "../Include/geometry.h"
using namespace std;

class Region {
	Region();

	vector<geometry::Vector> points;

	void reset() {
		points.clear();
	}
};

class Field {
public:
	Field();
	void addRegion(Region& _region);

	MovingObj rival, agent;
	vector<MovingObj> obstacles;

	vector<Region> regions;
};

#endif