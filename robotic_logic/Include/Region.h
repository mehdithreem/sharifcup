#ifndef robotic_logic_Region_h
#define robotic_logic_Region_h

#include <vector>
#include <utility>

#include "../Include/geometry.h"
#include "../Include/params.h"
using namespace std;

class Region {
public:
	vector<geometry::Vector> points;
	vector<pair<params::Color,params::Shape>> objects;
	int ID;

	Region(vector<geometry::Vector> _p);
	void reset();
	bool operator==(Region r);
	int size();

	vector< pair<geometry::Vector, bool> > destPoints;

	void addDestPoints(vector<geometry::Vector> _destPoints);  //Manual
	void calculateDestPoints(); //Automatic :D
};


#endif

