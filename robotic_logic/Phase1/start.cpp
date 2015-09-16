#include "../Include/Phase1.h"
#include <time.h>
//#include "./const.h" ---> // read rules file

int main() {
	Port Connection;
	Field field;
	RobotVision vision;
	vision.init();


	// vector<Point> points;
	// points.push_back(Point(300,100));
	// points.push_back(Point(300,250));
	// points.push_back(Point(400,100));
	// points.push_back(Point(400,250));
	// points.push_back(Point(470,130));
	// points.push_back(Point(470 , 130));
	// points.push_back(Point(410 , 1));
	// points.push_back(Point(310 , 142));
	// points.push_back(Point(123 , 169));
	  
	// vision.showPoints(points);
	// vision.preProcess(field);	
	
	// cerr << "----after init" << endl;
	
	bool end = false;
	while (!end) {
		bool pause = false;
		while (!pause && !end) {
			int degreeAtTarget;

			field.agent.updated = false;
			while (!field.agent.updated) vision.update(field);

			pair<geometry::Vector,geometry::Vector> goalDest; // first:target, second:dest
			std::vector<geometry::Vector> path;

			if (field.obstacles.size() < 0) {
				cout << "No obstacle found --> PAUSE mode" << endl;
				pause = true;
				continue;
			} else {

				cerr << "----after visionUpdate" << endl;
				
				// goalDest = field.bestTarget();
				goalDest.first = geometry::Vector(470,180);

				cerr << "----after bestTarget" << endl;

				// if there is no more objects, break, end = true
				// set degreeAtTarget

				// pathfind to target
				try {
					// path = ShortestPath(field.agent.COM, goalDest.first, field);
					
					

					path.push_back(field.agent.COM);
					// path.push_back(geometry::Vector(378,243));
					path.push_back(field.agent.COM + geometry::Vector(-325,125));
					path.push_back(field.agent.COM + geometry::Vector(-300,100));
					// path.push_back(field.agent.COM + geometry::Vector(-275,75));
					//path.push_back(field.agent.COM + geometry::Vector(-260,60));
					path.push_back(field.agent.COM + geometry::Vector(-250,50));
					path.push_back(field.agent.COM + geometry::Vector(-225,25));
					path.push_back(field.agent.COM + geometry::Vector(-200,0));
					//pa//th.push_back(field.agent.COM + geometry::Vector(-192,0));
					path.push_back(field.agent.COM + geometry::Vector(-175,0));
					//path//.push_back(field.agent.COM + geometry::Vector(-160,0));
					path.push_back(field.agent.COM + geometry::Vector(-150,0));
					//path.push_back(field.agent.COM + geometry::Vector(-125,0));
					path.push_back(field.agent.COM + geometry::Vector(-100,0));
					path.push_back(field.agent.COM + geometry::Vector(-50,0));
					path.push_back(field.agent.COM);

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
			if (path.size() > 0) x = (path[path.size()-1] - field.agent.COM).size();

			int count =0;
			clock_t t1, t2;
			t1 = clock();
			while (!pause /*&&  Connection.move(path, field.agent, x)*/) { // && not reached target
				// cin.ignore();
				field.agent.updated = false;
				count ++;
				clock_t t3, t4;
				t3 = clock();
				while (!field.agent.updated) vision.update(field);
				t4 = clock();
				//cout << "each :" << ((float)t-(float)t1)/CLOCKS_PER_SEC << endl;
				// Connection.fullStop();
				// cin.ignore();

				//cout << "--------fieldUpdate in move" << endl;
				if (count >= 20) pause = true;

				// if shasing then break
				// wall check
			}
			t2 = clock();

			float diff ((float)t2-(float)t1);

			cout << "----REACHED----" << endl;
			cout<<"#########"<<count<<endl;
			cout << diff/CLOCKS_PER_SEC << endl;
			end = true;
			Connection.fullStop();

			// while (!pause) { // && reached target && not lost obstacle && not reched destenation
			// 	// safe move

			// 	// if shasing then break
			// 	// wall check
			// }
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

	// std::vector<geometry::Vector> path;
	// path.push_back(geometry::Vector(470,130));

	// while (!field.agent.updated) vision.update(field);

	// int x = 100;
	// if (path.size() > 0) x = (path[path.size()-1] - field.agent.COM).size();

	// while (Connection.move(path, field.agent, x)) {
	// 	field.agent.updated = false;
	// 	while (!field.agent.updated) vision.update(field);
	// }
	
	// Connection.fullStop();

	// cin.ignore();

	// close port
	// delete
	return 0;
}
