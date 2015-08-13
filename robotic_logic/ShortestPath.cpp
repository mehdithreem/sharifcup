#include "ShortestPath.h"

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal , vector< pair<geometry::Vector , geometry::Vector> >* S){

  pair<geometry::Vector,geometry::Vector> startPair(start , cart2polar(start)),goalPair(goal,cart2polar(goal));
  S->push_back(startPair); S->push_back(goalPair);
  vector < vector<int> > visGraph = VisibiltyGraph(S);
  vector <vector <pair<int,double> > > weightedVisGraph;
  weightedVisGraph.resize(visGraph.size());
  for(int i=0 ; i<visGraph.size() ; i++)
    for(int j=0 ; j<visGraph[i].size() ; j++)
      if(visGraph[i][j])
        weightedVisGraph[i].push_back(make_pair(j , (S->at(i).first-S->at(j).first).size()));
  return AStar(S->size()-2 , S->size()-1 ,&weightedVisGraph);
}

vector<geometry::Vector> ShortestPath(MovingObj& agent, MovingObj& rival , vector<MovingObj>& obstacles, geometry::Vector goal) {
  vector<geometry::Vector> points;
  vector<geometry::Vector> path;

  vector< vector<bool> > matrix;
  vector< vector<int> > list;

  vector<int> numOfPoints;

  for(int i = 0; i < obstacles.size(); i++){
    points.insert(points.end(), obstacles[i].coords.begin(), obstacles[i].coords.end());
    numOfPoints.push_back(obstacles[i].coords.size());
  }

  points.insert(points.end(), rival.coords.begin(), rival.coords.end());

  points.push_back(agent.COM);
  points.push_back(goal);

  matrix = std::vector< std::vector<bool> >(points.size(), std::vector<bool>(points.size(),false));
  list = std::vector< std::vector<int> >(points.size());

  int penalty = 0;
  for(int j = 0; j < obstacles.size(); j++) {
    for(int i = penalty + 1; i < obstacles[j].coords.size() + penalty; i++) {
        matrix[i][i-1] = true;
        matrix[i-1][i] = true;

        list[i].push_back(i-1);
        list[i-1].push_back(i);
    }

    matrix[penalty][penalty + obstacles[i].coords.size()-1] = true;
    matrix[penalty + obstacles[i].coords.size()-1][penalty] = true;


    list[penalty].push_back(penalty + obstacles[i].coords.size()-1);
    list[penalty + obstacles[i].coords.size()-1].push_back(penalty);

    penalty += numOfPoints[j]; 
  }

  

}