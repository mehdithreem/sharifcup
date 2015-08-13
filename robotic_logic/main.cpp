//
//  main.cpp
//  robotic_logic
//
//  Created by Nahal on 8/8/15.
//  Copyright (c) 2015 Nahal. All rights reserved.
//

#include <iostream>
#include <vector>
#include "MovingObj.h"
#include "Vision.h"
#include "ShortestPath.h"

using namespace std;

int main(){
  MovingObj ourBot;
  MovingObj enemyBot;
  vector<MovingObj> obstacles;
  while(true){
    if(NewFrameIsReady()){
      update(ourBot, enemyBot, obstacles);
      // code to find the best dest 
      // determine the best dest is goal
      geometry::Vector goal(0,0);
      //Minkowski sum of −R,
      vector< pair<geometry::Vector,geometry::Vector> > points;
      points.insert(points.end() ,enemyBot.coords.begin() ,enemyBot.coords.end());
      for(int i=0 ; i<obstacles.size() ; i++)
      points.insert(points.end() ,obstacles[i].coords.begin() ,obstacles[i].coords.end());

      vector<geometry::Vector> sp = ShortestPath(ourBot.gravityCenter ,goal, &points);
    }
  }
}
