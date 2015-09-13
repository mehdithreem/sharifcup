#ifndef _PARAMS_
#define _PARAMS_

namespace params {
	enum Color { red, blue, green, yellow, violet };
	enum Shape { triangle, rectangle, polygon, circle };

	const vector<geometry::Vector> DESTPOINTS;
	const int LIMITDEST = 10;
	const int SPEED = 50;
}

#endif