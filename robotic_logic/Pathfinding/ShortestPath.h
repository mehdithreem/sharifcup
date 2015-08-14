#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "../Core/MovingObj.h"
#include "../Utility/geometry.h"

vector<geometry::Vector> ShortestPath( geometry::Vector start, geometry::Vector goal ,geometry::Graph& graph);

void VisibiltyGraph(Graph& graph); //has not been coded
vector<geometry::Vector> AStar(int start , int goal ,vector <vector <pair<int,double> > >* weightedVisGraph );// has not been coded

#endif
