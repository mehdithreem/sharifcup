#ifndef robotic_logic_Graph_h
#define robotic_logic_Graph_h

#include <vector>
#include "geometry.h"
#include "../Include/MovingObj.h"

class Graph{
	public:
		vector< vector<double> > matrix;
		vector< vector<int> > list;

		vector< geometry::Vector > nodes;
		
		int _size;
		Graph();

		void addComponent(vector<MovingObj>& obstacles);
		void addSingleNode(geometry::Vector newNode);
    void addEdge(int v ,int u);
		int size();

		void printNodes();
		void printMatrix();
		void printList();
		void print();
};

#endif
