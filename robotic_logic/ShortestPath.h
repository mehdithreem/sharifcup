#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "MovingObj.h"
#include "geometry.h"

vector<geometry::Vector> ShortestPath( geometry::Vector start, geometry::Vector goal ,geometry::Graph& graph);

void VisibiltyGraph(geometry::Graph& graph); //has not been coded
vector<geometry::Vector> AStar(int start , int goal ,vector <vector <pair<int,double> > >* weightedVisGraph );// has not been coded

#endif
