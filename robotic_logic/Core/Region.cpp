#include "../Include/Region.h"


Region::Region(vector<geometry::Vector> _p): points(_p) {
	geometry::sortCoordsByPolar(points);
}


bool Region::operator==(Region r){
	if(r.size()!=points.size())
		return false;
	for(int i=0 ; i<points.size() ; i++)
		if(r.points[i]!=points[i])
			return false;
	return true;
}


int Region::size(){return points.size();}

void Region::reset(){
	points.clear();
}

