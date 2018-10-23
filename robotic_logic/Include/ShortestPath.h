#ifndef robotic_logic_ShortestPath_h
#define robotic_logic_ShortestPath_h
#include <vector>
#include <utility>
#include "../Include/Graph.h"
#include "../Include/MovingObj.h"
#include "../Include/geometry.h"
#include "../Include/params.h"
#include "../Include/Field.h"

class Graph;
class Field;

// vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, Field& F );
vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, Field& F, int argc , char *argv[] ); 

void VisibiltyGraph(Graph& graph);
vector <int>  VisibileVertices(int i,Graph& garph);
vector<int> AStar(int start , int goal ,Graph& G);
std::vector<MovingObj> MinkowskiAll(const MovingObj& agent, MovingObj& rival, const std::vector<MovingObj>& obstacles);
#endif
