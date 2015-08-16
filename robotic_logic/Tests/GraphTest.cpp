#include "../Include/Graph.h"
#include "../Include/geometry.h"

void graphTest()
{
	Graph testG;

	testG.addSingleNode(geometry::Vector(24,15));
	testG.print();

	MovingObj testObj;
	std::vector<MovingObj> obstacles;

	obstacles.push_back(MovingObj());

	{	geometry::Vector v(10,10);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(1,1));
		vertices.push_back(geometry::Vector(3,2));
		vertices.push_back(geometry::Vector(2,5));

		obstacles[0].update(v, vertices);
	}
	
	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(5,3.5);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(9,8));
		vertices.push_back(geometry::Vector(16,9));
		vertices.push_back(geometry::Vector(10,11));
		vertices.push_back(geometry::Vector(12,12));

		obstacles[1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(7.5,8);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(11,3));
		vertices.push_back(geometry::Vector(14,6));
		vertices.push_back(geometry::Vector(14,3));
		vertices.push_back(geometry::Vector(11,6));

		obstacles[2].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(11,3.4);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(19,3));
		vertices.push_back(geometry::Vector(17,4));
		vertices.push_back(geometry::Vector(16,5));
		vertices.push_back(geometry::Vector(21,7));
		vertices.push_back(geometry::Vector(21,8));
		vertices.push_back(geometry::Vector(16,7));

		obstacles[3].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(10,7);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(4,12));
		vertices.push_back(geometry::Vector(3,10));
		vertices.push_back(geometry::Vector(3,11));
		vertices.push_back(geometry::Vector(6,8));
		vertices.push_back(geometry::Vector(6,11));

		obstacles[4].update(v, vertices);
	}

	testG.addComponent(obstacles);
	testG.print();
}

int main() {
	graphTest();

	return 0;
}