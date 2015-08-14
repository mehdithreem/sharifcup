//
//  main.cpp
//  robotic_logic
//
//  Created by Nahal on 8/8/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//

#include <iostream>
#include <vector>
#include "./Core/MovingObj.h"
#include "./Vision/Vision.h"
#include "./Pathfinding/ShortestPath.h"
#include "./Utility/Graph.h"
#include "./Utility/geometry.h"

using namespace std;

int main(){
	MovingObj agent;
	MovingObj rival;
	vector<MovingObj> obstacles;

	while(true){

		if(NewFrameIsReady()){
			update(agent, rival, obstacles);
				
			// code to find the best dest 
			// determine the best dest is goal
							
			geometry::Vector goal(0,0);
					
			//Minkowski sum of −R,
			//
			//vector<vector<geometry::Vector> > initCoordsForGraph;

			//for(int i=0 ; i<obstacles.size() ; i++)
			//  initCoordsForGraph.push_back(obstacles[i].coords);
			//initCoordsForGraph.push_back(rival.coords);
		
			obstacles.push_back(rival);
			vector<geometry::Vector> path = ShortestPath(agent.COM,goal,obstacles, rival);
			//vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, vector<MovingObj>& obstacles , MovingObj& rival);
		}
	}
}
