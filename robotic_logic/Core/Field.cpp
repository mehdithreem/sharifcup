#include "../Include/Field.h"

Field::Field(){}

void  Field::addRegion(Region& _region){
	for(int i=0 ; i<regions.size() ; i++)
		if(regions[i]==_region)
			return;
	regions.push_back(_region);
	return;
}


pair<geometry::Vector,geometry::Vector> Field::bestTarget(){
	// vector<target,dist>
	vector<pair<geometry::Vector, geometry::Vector>> targetDests;
	vector<int> cost;

	// find target and dists
	for (int i = 0; i < obstacles.size(); i++) {
		int regionIndex = 0;
		for(int j = 0; j < regions.size(); j++) {
			if (regions[j].ID == obstacles[i].regionID) {
				regionIndex = j;
				break;
			}
		}

		for (int j = 0; j < regions[regionIndex].destPoints.size(); j++) {
			pair<geometry::Vector, bool> dPt = regions[regionIndex].destPoints[j];
			if (dPt.second == true) {
				targetDests.push_back(make_pair((obstacles[i].COM - dPt.first)*1.5+dPt.first, dPt.first));
				cost.push_back(j*100);
			}
		}
	}

	// calculate obj intersections with lines
	for (int i = 0; i < obstacles.size(); i++) {
		for (int j = 0; j < targetDests.size(); j++) {
			if (obstacles[i].distWithCOM(targetDests.first, targetDests.seconds) <= obstacles[i].radious)
				cost[j] += 1000;

			cost[j] += (agent.COM - targetDests.first).size();

			if (obstacles[i].distWithCOM(targetDests.first, agent.COM) <= obstacles[i].radious)
				cost[j] += 100;
		}
	}

	int minIndex = 0;
	for(int i = 0; i < targetDests.size(); i++) {
		if (cost[minIndex] <= cost[i])
			minIndex = i;
	}
	
	return targetDests[minIndex];
}


