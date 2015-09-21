#ifndef _PARAMS_
#define _PARAMS_

namespace params {
	enum Color { red, blue, green, yellow, violet };
	enum Shape { triangle, rectangle, polygon, circle };

	const vector<geometry::Vector> DESTPOINTS;
	const int REACH_DIST = 10;

	const int ACC_DIST = 30;
	const int DEC_DIST = 70;

	const int SPEED = 70;
	const int minSPEED = 45;
	const int maxSPEED = 85;
}

namespace exceptions {
	class NoPath {};
}

#endif