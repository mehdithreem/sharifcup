#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "MovingObj.h"
#include "geometry.h"

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal , vector< pair<geometry::Vector , geometry::Vector> >* S);
vector <vector<int> > VisibiltyGraph(  vector< pair<geometry::Vector , geometry::Vector> >* S); //has not been coded
vector<geometry::Vector> AStar(geometry::Vector start, geometry::Vector goal , vector <vector <pair<int,double> > >* weightedVisGraph );// has not been coded

#endif
