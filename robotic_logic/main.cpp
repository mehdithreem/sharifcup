//
//  main.cpp
//  robotic_logic
//
//  Created by Nahal on 8/8/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//

#include <iostream>
#include <vector>
#include "./Include/MovingObj.h"
#include "./Include/Vision.h"
#include "./Include/ShortestPath.h"
#include "./Include/Graph.h"
#include "./Include/geometry.h"

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
			

			// union obstacles

			obstacles.push_back(rival);
			vector<geometry::Vector> path = ShortestPath(agent.COM,goal,obstacles, rival);
		}
	}
}
