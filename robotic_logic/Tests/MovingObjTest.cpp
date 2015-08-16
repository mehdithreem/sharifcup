#include "../Include/MovingObj.h"
#include "../Include/geometry.h"

void testUpdate() {
	MovingObj testObj;

	geometry::Vector v(10,10);

	std::vector<geometry::Vector> vertices;

	// vertices.push_back(geometry::Vector(10,10));
	// vertices.push_back(geometry::Vector(0,0));
	// vertices.push_back(geometry::Vector(10,4));
	// vertices.push_back(geometry::Vector(2,7));

	vertices.push_back(geometry::Vector(1,0));
	vertices.push_back(geometry::Vector(-1,0));
	vertices.push_back(geometry::Vector(0,-1));
	vertices.push_back(geometry::Vector(0,1));
	vertices.push_back(geometry::Vector(0,2));

	testObj.update(v, vertices);

	testObj.print();

	//sort by wrong order
}

int main() {
	testUpdate();

	return 0;
}