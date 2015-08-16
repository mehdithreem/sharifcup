#include "Graph.h"
#include "geometry.h"

void graphTest()
{
	Graph testG;

	testG.addSingleNode(new geometry::Vector(24,15));

	MovingObj testObj;

	geomtry::Vector v(10,10);

	std::vector<geomtry::Vector> vertices;

	vertices.push_back(new geomtry::Vector(7,8));
	vertices.push_back(new geomtry::Vector(0,0));
	vertices.push_back(new geomtry::Vector(2,10));
	vertices.push_back(new geomtry::Vector(3,6));

	testObj.update(v, vertices);


}

int main() {
	graphTest();

	return 0;
}