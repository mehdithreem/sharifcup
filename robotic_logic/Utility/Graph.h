#ifndef robotic_logic_Graph_h
#define robotic_logic_Graph_h

#include <vector>
#include "geometry.h"
#include "../Core/MovingObj.h"

class Graph{
	public:
		vector< vector<double> > matrix;
		vector< vector<int> > list;

		vector< geometry::Vector > nodes;
		
		int _size; // num of vertices 
		Graph();

		void addComponent(vector<MovingObj>& obstacles);
		void addSingleNode(geometry::Vector newNode);
		int size() { return list.size(); }
};

#endif