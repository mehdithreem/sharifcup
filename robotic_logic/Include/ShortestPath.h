#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "../Include/MovingObj.h"
#include "../Include/geometry.h"
#include "../Include/Graph.h"

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, vector<MovingObj>& obstacles , MovingObj& rival);

void VisibiltyGraph(Graph& graph); //has not been coded
vector<int> AStar(int start , int goal ,Graph& G);

#endif
