#include <utility>
#include "../Include/Phase1.h"
#include "../Include/Field.h"

//#include "./const.h"   --->	// read rules file

int main() {
	Field field;
	//Vision vision;
	//vision.preProcess(field);	
	
	bool end = false;
	while (!end) {
		bool pause = false;
		while (!pause) {	
			geometry::Vector target, destenation;
			int degreeAtTarget;
			//vision.update(field);
			// choose best target and it's destionation
			pair<geometry::Vector,geometry::Vector> tar&dest = field.bestTar&dest();
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
