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

