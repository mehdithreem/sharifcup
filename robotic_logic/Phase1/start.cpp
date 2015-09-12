#include <utility>
#include "../Include/Phase1.h"
#include "../Include/Field.h"
#include "../Include/geometry.h"
#include "../Include/Vision.h"
#include "../Include/Graph.h"


const vector<geometry::Vector> DESTPOINTS;
//#include "./const.h"   --->	// read rules file

int main() {
	Field field;
	RobotVision vision;
	vision.init();
	//vision.preProcess(field);	
	
	bool end = false;
	while (!end) {
		bool pause = false;
		while (!pause) {	
			geometry::Vector target, destenation;
			int degreeAtTarget;
			vision.update(field);
			Graph g;
			for(int i=0 ; i<DESTPOINTS.size() ; i++)
				g.addSingleNode(DESTPOINTS[i]);
			pair<geometry::Vector,geometry::Vector> goalDest = field.bestTarget();
			// 		if there is no more objects, break, end = true
			// set degreeAtTarget

			std::vector<geometry::Vector> path;
			// pathfind to target
			// 		if there is no path then what???
			
			while (!pause) { // && not reached target
				// move through path

				// if shasing then break
				// wall check
			}

			while (!pause) { // && reached target && not lost obstacle && not reched destenation
				// safe move

				// if shasing then break
				// wall check
			}
		}

		while (pause) {
			// full stop
			// input for continue
			// while pause
		}
	}

	// close port
	// delete
	return 0;
}
