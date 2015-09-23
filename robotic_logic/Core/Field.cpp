#include "../Include/Field.h"

Field::Field(){}

pair<geometry::Vector,geometry::Vector> Field::bestTarget(){
	// vector<target,dist>
	vector<pair<geometry::Vector, geometry::Vector>> targetDests;
	vector<int> cost;
	cerr << "----in bestTarget 1" << endl;
	cerr << "-------- obstacles.size "  << obstacles.size() << endl;

	// find target and dists
	for (int i = 0; i < obstacles.size(); i++) {
		int regionIndex = 0;
		for(int j = 0; j < regions.size(); j++) {
			if (regions[j].ID == obstacles[i].regionID) {
				regionIndex = j;
				break;
			}
		}

		cerr << "----in bestTarget 2 :regionIndex = " << regionIndex << " color: " << getColorName(obstacles[i].color) << endl;

		for (int j = 0; j < regions[regionIndex].destPoints.size(); j++) {
			cerr << regions[regionIndex].destPoints[j].first << endl;
			pair<geometry::Vector, bool> dPt = regions[regionIndex].destPoints[j];
			if (dPt.second == true) {
				targetDests.push_back(make_pair((obstacles[i].COM - dPt.first)/(1/1.5)+dPt.first, dPt.first));
				cost.push_back(j*100);
			}
		}

		cerr << "----in bestTarget 3" << endl;

	}

	cerr << "----in bestTarget 4 :targetDests.size() = " << targetDests.size() << endl;

	// calculate obj intersections with lines
	for (int i = 0; i < obstacles.size(); i++) {
		for (int j = 0; j < targetDests.size(); j++) {
			if (obstacles[i].distWithCOM(targetDests[j].first, targetDests[j].second) <= obstacles[i].radious)
				cost[j] += 1000;

			cost[j] += (agent.COM - targetDests[j].first).size();

			if (obstacles[i].distWithCOM(targetDests[j].first, agent.COM) <= obstacles[i].radious)
				cost[j] += 100;
		}
	}

	int minIndex = 0;
	for(int i = 0; i < targetDests.size(); i++) {
		if (cost[minIndex] <= cost[i])
			minIndex = i;
	}
	
	cerr << "----in bestTarget 5" << endl;

	return targetDests[minIndex];
}


