#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "MovingObj.h"
#include "geometry.h"

vector<geometry::Vector> ShortestPath(MovingObj& agent, MovingObj& rival , vector<MovingObj>& obstacles, geometry::Vector goal);

vector <vector<int> > VisibiltyGraph( const vector< pair<geometry::Vector , geometry::Vector> >* S); //has not been coded
vector<geometry::Vector> AStar(int start , int goal ,vector <vector <pair<int,double> > >* weightedVisGraph );// has not been coded

#endif
