#include "../Include/Phase1.h"
#include <time.h>
//#include "./const.h" ---> // read rules file

int main() {
	// Port Connection;
	Field field;
	RobotVision vision;
	vision.init();

	vision.set();

	//vision.preprocess(field);
		
	// bool end = false;
	// while (!end) {
	// 	bool pause = false;
	// 	while (!pause && !end) {
	// 		int degreeAtTarget;

	// 		field.agent.updated = false;
	// 		while (!field.agent.updated) vision.update(field,true);
	// 		cout << "obstacles size: " << field.obstacles.size() << endl;

	// 		for(int i = 0; i < field.obstacles.size(); i++){
	// 			cout << "obj#" << i << ": " << field.obstacles[i].COM << endl;
	// 		}

	// 		cin.ignore();

	// 		pair<geometry::Vector,geometry::Vector> goalDest; // first:target, second:dest
	// 		std::vector<geometry::Vector> path;
	// 		if (field.obstacles.size() < 0) {
	// 			cout << "No obstacle found --> PAUSE mode" << endl;
	// 			pause = true;
	// 			continue;
	// 		} else {
	// 			cerr << "----after visionUpdate" << endl;
				
	// 			goalDest = field.bestTarget();

	// 			cout << "target and dest: " << goalDest.first << " -> " << goalDest.second << endl;

	// 			cin.ignore();
	// 			// if there is no more objects, break, end = true
	// 			// set degreeAtTarget

	// 			// pathfind to target
	// 			try {
	// 				path = ShortestPath(field.agent.COM, goalDest.first, field);
			
	// 				// path.push_back(field.agent.COM);
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,100));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,0));

	// 				// path.push_back(field.agent.COM);
	// 				// path.push_back(field.agent.COM + geometry::Vector(-100,100));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,100));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-300,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,-100));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-100,-100));
					
	// 				// path.push_back(field.agent.COM);
	// 				// path.push_back(field.agent.COM + geometry::Vector(-300,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-300,-200));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-300,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,-200));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-200,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-100,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-100,-200));
	// 				// path.push_back(field.agent.COM + geometry::Vector(-100,0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(0,-0));
	// 				// path.push_back(field.agent.COM + geometry::Vector(0,-200));

	// 				// path.push_back(field.agent.COM);
	// 				// path.push_back(geometry::Vector(202,291));


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

	// 		int index = path.size()-1;
	// 		vector<int> pathSpeeds;
	// 		bool rotating = false;

	// 		preprocessPath(path, pathSpeeds);

	// 		while (!pause && Connection.move(path, pathSpeeds ,field.agent, index,rotating)) { // && not reached target
	// 			field.agent.updated = false;
	// 			while (!field.agent.updated) vision.update(field,false);

	// 			// if shasing then break
	// 			// wall check
	// 		}

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

	// float var = 25.64;
	// for(int i=0 ; i<30 ; i++){
	// 	Connection.talkToSetare(0,0,0);

	// 	usleep(12*var*1000);
	// 	Connection.fullStop();
	// 	usleep(400*1000);
	// }


	// while(field.agent.direction < 70 ){
	// 	Connection.talkToSetare(0,0,0);				
	// 	cout << "---- degree is :" << field.agent.direction << endl;
	// 	vision.update(field);		
	// }
	// Connection.fullStop();



	// Connection.talkToSetare(70,0,5);

	// usleep(var*10*1000);

	cin.ignore();

	

	// close port
	// delete
	return 0;
}
