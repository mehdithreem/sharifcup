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

void Region::addDestPoints(vector<geometry::Vector> _destPoints) {
	geometry::sortCoordsByPolar(_destPoints);

	for(geometry::Vector point : _destPoints) {
		destPoints.push_back(make_pair(point, false));
	}

	return;
}