#ifndef robotic_logic_Region_h
#define robotic_logic_Region_h
#include "../Include/geometry.h"
using namespace std;

class Region {
	public:
	vector<geometry::Vector> points;
	Region(vector<geometry::Vector> _p);
	void reset();
	bool operator==(Region r);
	int size();
};


#endif

