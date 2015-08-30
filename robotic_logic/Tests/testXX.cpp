#include <Python.h>
#include "../Include/Graph.h"
#include "../Include/geometry.h"
#include "../Include/ShortestPath.h"
#include "../Include/clipper.h"

void graphTest(int argc, char *argv[])
{
	Graph testG;

	// testG.print();
	MovingObj agent;
	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(185,30));
		vertices.push_back(geometry::Vector(241,36));
		vertices.push_back(geometry::Vector(239,73));
		vertices.push_back(geometry::Vector(182,61));

		agent.update(v, vertices);
	}

	testG.addSingleNode(agent.COM);

	MovingObj rival;
	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(35,291));
		vertices.push_back(geometry::Vector(54,291));
		vertices.push_back(geometry::Vector(54,303));
		vertices.push_back(geometry::Vector(41,302));

		rival.update(v, vertices);
	}

	std::vector<MovingObj> obstacles;

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(86,119));
		vertices.push_back(geometry::Vector(72,157));
		vertices.push_back(geometry::Vector(39,159));
		vertices.push_back(geometry::Vector(75,175));
		vertices.push_back(geometry::Vector(75,175));
		vertices.push_back(geometry::Vector(87,216));
		vertices.push_back(geometry::Vector(99,173));
		vertices.push_back(geometry::Vector(135,165));
		vertices.push_back(geometry::Vector(96,157));

	obstacles[obstacles.size()-1].update(v, vertices);
}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(135,130));
		vertices.push_back(geometry::Vector(157,156));
		vertices.push_back(geometry::Vector(164,178));
		vertices.push_back(geometry::Vector(152,189));
		vertices.push_back(geometry::Vector(144,219));
		vertices.push_back(geometry::Vector(153,230));
		vertices.push_back(geometry::Vector(175,230));
		vertices.push_back(geometry::Vector(235,198));
		vertices.push_back(geometry::Vector(223,143));

	obstacles[obstacles.size()-1].update(v, vertices);
}

	std::vector<MovingObj> finalObstacles;
	finalObstacles = MinkowskiAll(agent, rival, obstacles);

	testG.addComponent(finalObstacles);

	testG.addSingleNode(geometry::Vector(290,290));

	VisibiltyGraph(testG);

	// cerr << "before visualize" << endl;
	std::vector<int> path;
	path = AStar(0 , testG.size()-1 ,testG);

	testG.visualize(argc, argv, path, agent, rival, obstacles);

	return;
}

int main(int argc, char *argv[]) {

	graphTest(argc, argv);

	return 0;
}
