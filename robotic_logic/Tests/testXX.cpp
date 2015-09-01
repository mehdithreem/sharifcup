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

		vertices.push_back(geometry::Vector(23,35));
		vertices.push_back(geometry::Vector(89,30));
		vertices.push_back(geometry::Vector(87,65));
		vertices.push_back(geometry::Vector(26,84));

		agent.update(v, vertices);
	}

	testG.addSingleNode(agent.COM);

	MovingObj rival;
	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(42,278));
		vertices.push_back(geometry::Vector(67,277));
		vertices.push_back(geometry::Vector(68,304));
		vertices.push_back(geometry::Vector(38,309));

		rival.update(v, vertices);
	}

	std::vector<MovingObj> obstacles;

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(91,112));
		vertices.push_back(geometry::Vector(74,139));
		vertices.push_back(geometry::Vector(35,159));
		vertices.push_back(geometry::Vector(78,170));
		vertices.push_back(geometry::Vector(77,194));
		vertices.push_back(geometry::Vector(140,156));
		vertices.push_back(geometry::Vector(105,147));

	obstacles[obstacles.size()-1].update(v, vertices);
}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(115,130));
		vertices.push_back(geometry::Vector(173,157));
		vertices.push_back(geometry::Vector(110,193));
		vertices.push_back(geometry::Vector(110,193));
		vertices.push_back(geometry::Vector(119,229));
		vertices.push_back(geometry::Vector(243,199));
		vertices.push_back(geometry::Vector(231,121));
		vertices.push_back(geometry::Vector(129,104));

	obstacles[obstacles.size()-1].update(v, vertices);
}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(164,28));
		vertices.push_back(geometry::Vector(244,32));
		vertices.push_back(geometry::Vector(244,86));
		vertices.push_back(geometry::Vector(160,76));

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
