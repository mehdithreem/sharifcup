#include "../Include/Phase1.h"
#include <time.h>
//#include "./const.h" ---> // read rules file

int main() {
	Port Connection;
	Field field;
	RobotVision vision;
	vision.init();
		
	// bool end = false;
	// while (!end) {
	// 	bool pause = false;
	// 	while (!pause && !end) {
	// 		int degreeAtTarget;

	// 		field.agent.updated = false;
	// 		while (!field.agent.updated) vision.update(field);

	// 		pair<geometry::Vector,geometry::Vector> goalDest; // first:target, second:dest
	// 		std::vector<geometry::Vector> path;

	// 		if (field.obstacles.size() < 0) {
	// 			cout << "No obstacle found --> PAUSE mode" << endl;
	// 			pause = true;
	// 			continue;
	// 		} else {

	// 			cerr << "----after visionUpdate" << endl;
				
	// 			// goalDest = field.bestTarget();
	// 			goalDest.first = geometry::Vector(470,180);

	// 			cerr << "----after bestTarget" << endl;

	// 			// if there is no more objects, break, end = true
	// 			// set degreeAtTarget

	// 			// pathfind to target
	// 			try {
	// 				// path = ShortestPath(field.agent.COM, goalDest.first, field);
			
	// 				path.push_back(field.agent.COM);
	// 				// path.push_back(geometry::Vector(378,243));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-325,125));
	// 				path.push_back(field.agent.COM + geometry::Vector(-200,100));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-250,50));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-225,25));
	// 				path.push_back(field.agent.COM + geometry::Vector(-200,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-175,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-150,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-100,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-50,0));
	// 				// path.push_back(field.agent.COM);

	// 				vision.showPoints(path);

	// 				cout << "PATH: ";
	// 				for (geometry::Vector pt : path) {
	// 					cout << " " << pt;
	// 				}
	// 				cout << endl;

	// 			} catch (exceptions::NoPath) {
	// 				// if there is no path then what???
	// 				cout << "No Path found --> PAUSE mode" << endl;
	// 				pause = true;
	// 				continue;
	// 			}

	// 			cerr << "----end of bestTarget" << endl;
	// 		}

	// 		int x = 100;
	// 		if (path.size() > 0) x = (path[path.size()-1] - field.agent.COM).size();

	// 		while (!pause && Connection.move(path, field.agent, x)) { // && not reached target
	// 			field.agent.updated = false;
	// 			while (!field.agent.updated) vision.update(field);

	// 			// if shasing then break
	// 			// wall check
	// 		}
	// 		t2 = clock();

	// 		float diff ((float)t2-(float)t1);

	// 		cout << "----REACHED----" << endl;
	// 		end = true;
	// 		Connection.fullStop();

	// 		// while (!pause) { // && reached target && not lost obstacle && not reched destenation
	// 		// 	// safe move

	// 		// 	// if shasing then break
	// 		// 	// wall check
	// 		// }
	// 	}

	// 	while (pause && !end) {
	// 		int input = 0;
	// 		while (input != 1) {
	// 			cout << "ENTER 1 to continue: ";
	// 			cin >> input;
	// 		}

	// 		pause = false;
	// 		// full stop
	// 		// input for continue
	// 		// while pause
	// 	}
	// }
	
	Connection.talkToSetare(100,-180,0);

	cin.ignore();

	Connection.fullStop();

	// close port
	// delete
	return 0;
}
