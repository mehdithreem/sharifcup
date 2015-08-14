#include "ShortestPath.h"
#include "../Utility/Graph.h"

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, vector<MovingObj>& obstacles , MovingObj& rival ) {
	
	Graph G;

	G.addSingleNode(start);
	G.addSingleNode(goal);

	G.addComponet(obstacles.push_back(rival));
	obstacles.pop_back();

	// //add start and goal to graph
	// vector<vector<geometry::Vector> > initCoordsForGraph;

	// for(int i=0 ; i<obstacles.size() ; i++)
	// 	initCoordsForGraph.push_back(obstacles[i].coords);
	
	// initCoordsForGraph.push_back(rival.coords);
	// geometry::Graph initialGraph(initCoordsForGraph);

	// initialGraph.addNode(); initialGraph.addNode();
	
	VisibiltyGraph(G);
}
