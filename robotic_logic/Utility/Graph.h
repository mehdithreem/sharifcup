
#include <vector>
#include "geometry.h"
#include "../Core/MovingObj.h"

class Graph{
	public:
		vector< vector<double> > matrix;
		vector< vector<int> > list;

		vector< geometry::vector > nodes;
	
		Graph();

		int size; // num of vertices

		void addComponent(vector<MovingObj>& obstacles);
		void addSingleNode(geometry::vector newNode);
};