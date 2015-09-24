#include "../Include/Phase1.h"
#include <time.h>
//#include "./const.h" ---> // read rules file

int main(int argc, char *argv[]) {
	Port Connection;
	Field field;
	RobotVision vision;
	vision.init();

	vision.set();

	return 0;

	// while(true) {
	// 	vision.update(field, true);
	// }

	//vision.preprocess(field);
		
	bool end = false;
	while (!end) {
		bool pause = false;
		while (!pause && !end) {
			int degreeAtTarget;

			vector<geometry::Vector> region1, region2, region3, destPoints;
			region1.push_back(geometry::Vector(50,200));
			region1.push_back(geometry::Vector(50,150));
			region1.push_back(geometry::Vector(0,150));
			region1.push_back(geometry::Vector(0,200));

			vision.showPoints(region1);
			field.regions.push_back(Region(region1));
			destPoints.clear();
			destPoints.push_back(geometry::Vector(25,175));
			vision.showPoints(destPoints);
			field.regions[0].ID = 0;
			field.regions[0].addDestPoints(destPoints);

			region2.push_back(geometry::Vector(190,70));
			region2.push_back(geometry::Vector(300,70));
			region2.push_back(geometry::Vector(190,0));
			region2.push_back(geometry::Vector(300,0));

			vision.showPoints(region2);
			field.regions.push_back(Region(region2));
			destPoints.clear();
			destPoints.push_back(geometry::Vector(230,35));
			destPoints.push_back(geometry::Vector(270,35));
			vision.showPoints(destPoints);
			field.regions[1].ID = 1;
			field.regions[1].addDestPoints(destPoints);

			region3.push_back(geometry::Vector(300,350));
			region3.push_back(geometry::Vector(360,350));
			region3.push_back(geometry::Vector(300,400));
			region3.push_back(geometry::Vector(360,400));

			vision.showPoints(region3);
			field.regions.push_back(Region(region3));
			destPoints.clear();
			destPoints.push_back(geometry::Vector(330,375));
			vision.showPoints(destPoints);
			field.regions[2].ID = 2;
			field.regions[2].addDestPoints(destPoints);


			field.agent.updated = false;
			while (!field.agent.updated) vision.update(field,true);
			cout << "obstacles size: " << field.obstacles.size() << endl;
			field.agent.coords.clear();
			field.agent.coords.push_back(field.agent.COM+geometry::Vector(25,25));
			field.agent.coords.push_back(field.agent.COM+geometry::Vector(25,-25));
			field.agent.coords.push_back(field.agent.COM+geometry::Vector(-25,-25));
			field.agent.coords.push_back(field.agent.COM+geometry::Vector(-25,25));

			for(int i = 0; i < field.obstacles.size(); i++){
				cout << "obj#" << i << " (" << getColorName(field.obstacles[i].color) << "): " << field.obstacles[i].COM << endl;
				if (field.obstacles[i].color == yellow) field.obstacles[i].regionID = 1;
				else if (field.obstacles[i].color == green) field.obstacles[i].regionID = 1;
				else if (field.obstacles[i].color == red) field.obstacles[i].regionID = 0;
				else field.obstacles[i].regionID = 2;
			}

			// cin.ignore();

			pair<geometry::Vector,geometry::Vector> goalDest; // first:target, second:dest
			params::Color targetColor;

			std::vector<geometry::Vector> path;
			bool done = false;
			
			if (field.obstacles.size() == 0) {
				cout << "No obstacle found --> PAUSE mode" << endl;
				pause = true;
				continue;
			} else {
				cerr << "----after visionUpdate" << endl;

				
				goalDest = field.bestTarget(targetColor, done);

				if (done) {
					cout << "end" << endl;
					goalDest.first = field.regions[2].destPoints[0].first;
				}
				else cout << "target and dest: " << goalDest.first << " -> " << goalDest.second << " :color " << params::getColorName(targetColor) << endl;

				// cin.ignore();
				// if there is no more objects, break, end = true
				// set degreeAtTarget

				// pathfind to target
				try {
					field.agent.print();
					path = ShortestPath(field.agent.COM, goalDest.first, field, argc, argv);
			
					// path.push_back(field.agent.COM);
					// path.push_back(field.agent.COM + geometry::Vector(-200,100));
					// path.push_back(field.agent.COM + geometry::Vector(-200,0));

					// path.push_back(field.agent.COM);
					// path.push_back(field.agent.COM + geometry::Vector(-100,100));
					// path.push_back(field.agent.COM + geometry::Vector(-200,100));
					// path.push_back(field.agent.COM + geometry::Vector(-300,0));
					// path.push_back(field.agent.COM + geometry::Vector(-200,-100));
					// path.push_back(field.agent.COM + geometry::Vector(-100,-100));
					
					// path.push_back(field.agent.COM);
					// path.push_back(field.agent.COM + geometry::Vector(-300,0));
					// path.push_back(field.agent.COM + geometry::Vector(-300,-200));
					// path.push_back(field.agent.COM + geometry::Vector(-300,0));
					// path.push_back(field.agent.COM + geometry::Vector(-200,0));
					// path.push_back(field.agent.COM + geometry::Vector(-200,-200));
					// path.push_back(field.agent.COM + geometry::Vector(-200,0));
					// path.push_back(field.agent.COM + geometry::Vector(-100,0));
					// path.push_back(field.agent.COM + geometry::Vector(-100,-200));
					// path.push_back(field.agent.COM + geometry::Vector(-100,0));
					// path.push_back(field.agent.COM + geometry::Vector(0,-0));
					// path.push_back(field.agent.COM + geometry::Vector(0,-200));

					// path.push_back(field.agent.COM);
					// path.push_back(geometry::Vector(202,291));


					vision.showPoints(path);

					cout << "PATH: ";
					for (geometry::Vector pt : path) {
						cout << " " << pt;
					}
					cout << endl;

				} catch (exceptions::NoPath) {
					// if there is no path then what???
					cout << "No Path found --> PAUSE mode" << endl;
					pause = true;
					continue;
				}

				cerr << "----end of bestTarget" << endl;
			}

			int x = 100;

			int index = path.size()-1;
			vector<int> pathSpeeds;
			bool rotating = false;

			preprocessPath(path, pathSpeeds);

			while (!pause && Connection.move(path, pathSpeeds ,field.agent, index, rotating)) { // && not reached target
				field.agent.updated = false;
				while (!field.agent.updated) vision.update(field,false);

				// if shasing then break
				// wall check
			}

			cout << "----REACHED----" << endl;
			Connection.fullStop();
			if (done) {
				cout << "-----END------" << endl;
				end = true;
				break;
			}
			// cin.ignore();

			// degreeAtTarget = (goalDest.second - goalDest.first).angle();
			rotating = false;
			bool lost = false;
			bool pushing = false;

			preprocessPath(path, pathSpeeds);

			while (!pause && Connection.safeMove(goalDest.second, field.agent, rotating) && !lost) { // && not reached target
				field.agent.updated = false;
				while (!field.agent.updated) vision.update(field,true);

				for(int i = 0; i < field.obstacles.size(); i++) {
					if (field.obstacles[i].color == targetColor) {
						if (pushing && (field.obstacles[i].COM - field.agent.COM).size() >= params::LOST_LIMIT){
							cout << "--------OBSTACLE LOST :(-----------" << params::getColorName(targetColor) << endl;
							cout << (field.obstacles[i].COM - field.agent.COM).size() << endl;
							lost = true;
							break;
						}
						else if ((field.obstacles[i].COM - field.agent.COM).size() < params::LOST_LIMIT - 20) {
							// Connection.fullStop();
							cout << "----PUSHING-----" << endl;
							// cin.ignore();
							pushing = true;
						}
					}
				}
				// if shasing then break
				// wall check
			}

				Connection.fullStop();
			if (!lost) {
				cout << "-----DONE------" << endl;
				// cin.ignore();
			}
		}

		while (pause && !end) {
			int input = 0;
			while (input != 1) {
				cout << "ENTER 1 to continue: ";
				cin >> input;
			}

			pause = false;
			// full stop
			// input for continue
			// while pause
		}
	}

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
