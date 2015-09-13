#ifndef _PARAMS_
#define _PARAMS_

namespace params {
	enum Color { red, blue, green, yellow, violet };
	enum Shape { triangle, rectangle, polygon, circle };

	const vector<geometry::Vector> DESTPOINTS;
	const int LIMITDEST = 40;
	const int SPEED = 50;
	const int minSPEED = 20;
	const int maxSPEED = 55;
}

namespace exceptions {
	class NoPath {};
}

#endif