#include <Python.h>
#include "../Include/Graph.h"
#include "../Include/geometry.h"
#include "../Include/ShortestPath.h"

void graphTest(int argc, char *argv[])
{
	Graph testG;

	testG.addSingleNode(geometry::Vector(24,15));
	// testG.print();

	MovingObj testObj;
	std::vector<MovingObj> obstacles;

	obstacles.push_back(MovingObj());

	{	geometry::Vector v(10,10);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(1*15,1*15));
		vertices.push_back(geometry::Vector(3*15,2*15));
		vertices.push_back(geometry::Vector(2*15,5*15));

		obstacles[0].update(v, vertices);
	}
	
	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(5,3.5);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(9*15,8*15));
		vertices.push_back(geometry::Vector(16*15,9*15));
		vertices.push_back(geometry::Vector(10*15,11*15));
		vertices.push_back(geometry::Vector(12*15,12*15));

		obstacles[1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(7.5,8);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(11*15,3*15));
		vertices.push_back(geometry::Vector(14*15,6*15));
		vertices.push_back(geometry::Vector(14*15,3*15));
		vertices.push_back(geometry::Vector(11*15,6*15));

		obstacles[2].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(11,3.4);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(19*15,3*15));
		vertices.push_back(geometry::Vector(17*15,4*15));
		vertices.push_back(geometry::Vector(16*15,5*15));
		vertices.push_back(geometry::Vector(21*15,7*15));
		vertices.push_back(geometry::Vector(21*15,8*15));
		vertices.push_back(geometry::Vector(16*15,7*15));

		obstacles[3].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(10,7);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(4*15,12*15));
		vertices.push_back(geometry::Vector(3*15,10*15));
		vertices.push_back(geometry::Vector(3*15,11*15));
		vertices.push_back(geometry::Vector(6*15,8*15));
		vertices.push_back(geometry::Vector(6*15,11*15));

		obstacles[4].update(v, vertices);
	}

	testG.addComponent(obstacles);
	testG.print();

	// cerr << "befor first visualiztion" << endl;

	testG.visualize(argc, argv);

	// VisibiltyGraph(testG);

	// testG.visualize(argc, argv);

	return;
}

int main(int argc, char *argv[]) {

	graphTest(argc, argv);

	return 0;
}
