#ifndef robotic_logic_Graph_h
#define robotic_logic_Graph_h

#include <vector>
#include "geometry.h"
#include "../Include/MovingObj.h"
#include "../Include/Field.h"

class Graph{
public:
	vector< vector<int> > matrix;
	vector< vector<int> > list;

	vector< geometry::Vector > nodes;

	vector< int > obNum;
	
	int _size;
	Graph();
	//void makeGraphBasedOnField(Field& field);
	void addComponent(vector<MovingObj>& obstacles);
	void addSingleNode(geometry::Vector newNode);
	
	void addEdge(int v ,int u);
	int size();

	void printNodes();
	void printMatrix();
	void printList();
	void print();

	void visualize(int argc, char *argv[], std::vector<int> path,
		const MovingObj& agent, const MovingObj& rival, const std::vector<MovingObj>& obstacles);

};

#endif
