#include "../Include/Field.h"

Field::Field(){}

void  Field::addRegion(Region& _region){
	for(int i=0 ; i<regions.size() ; i++)
		if(regions[i]==_region)
			return;
	regions.push_back(_region);
	return;
}


pair<geometry::Vector,geometry::Vector> Field:: bestTarget(){
	pair<geometry::Vector,geometry::Vector> result;
	///:?
	return result;
}


