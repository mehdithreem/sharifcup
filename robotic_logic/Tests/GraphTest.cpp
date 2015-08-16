#include "../Include/Graph.h"
#include "../Include/geometry.h"

void graphTest()
{
	Graph testG;

	testG.addSingleNode(geometry::Vector(24,15));

	MovingObj testObj;
	std::vector<MovingObj> obstacles;

	obstacles.push_back(MovingObj());

	{	geomtry::Vector v(10,10);
		std::vector<geomtry::Vector> vertices;

		vertices.push_back(geometry::Vector(10,10));
		vertices.push_back(geometry::Vector(0,0));
		vertices.push_back(geometry::Vector(10,4));
		vertices.push_back(geometry::Vector(2,7));

		obstacles[0].update(v, vertices);
	}
	
	obstacles.push_back(MovingObj());

	{
		geomtry::Vector v(5,3.5);
		std::vector<geomtry::Vector> vertices;

		vertices.push_back(geometry::Vector(10,10));
		vertices.push_back(geometry::Vector(0,0));
		vertices.push_back(geometry::Vector(10,4));
		vertices.push_back(geometry::Vector(2,7));

		obstacles[1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geomtry::Vector v(7.5,8);
		std::vector<geomtry::Vector> vertices;

		vertices.push_back(geometry::Vector(10,10));
		vertices.push_back(geometry::Vector(0,0));
		vertices.push_back(geometry::Vector(10,4));
		vertices.push_back(geometry::Vector(2,7));

		obstacles[2].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geomtry::Vector v(11,3.4);
		std::vector<geomtry::Vector> vertices;

		vertices.push_back(geometry::Vector(10,10));
		vertices.push_back(geometry::Vector(0,0));
		vertices.push_back(geometry::Vector(10,4));
		vertices.push_back(geometry::Vector(2,7));

		obstacles[3].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geomtry::Vector v(10,7);
		std::vector<geomtry::Vector> vertices;

		vertices.push_back(geometry::Vector(10,10));
		vertices.push_back(geometry::Vector(0,0));
		vertices.push_back(geometry::Vector(10,4));
		vertices.push_back(geometry::Vector(2,7));

		obstacles[4].update(v, vertices);
	}
}

int main() {
	graphTest();

	return 0;
}