#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "../Core/MovingObj.h"
#include "../Utility/geometry.h"
#include "../Utility/Graph.h"

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, vector<MovingObj>& obstacles , MovingObj& rival);

void VisibiltyGraph(Graph& graph); //has not been coded
vector<int> AStar(int start , int goal ,Graph& G);

#endif
