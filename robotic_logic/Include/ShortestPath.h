#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "../Include/Graph.h"
#include "../Include/MovingObj.h"
#include "../Include/geometry.h"

class Graph;

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, Graph& G);

void VisibiltyGraph(Graph& graph);
vector <int>  VisibileVertices(int i,Graph& garph);
vector<int> AStar(int start , int goal ,Graph& G);
std::vector<MovingObj> MinkowskiAll(const MovingObj& agent, MovingObj& rival, const std::vector<MovingObj>& obstacles);
#endif
