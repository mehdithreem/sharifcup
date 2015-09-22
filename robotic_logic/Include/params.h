#ifndef _PARAMS_
#define _PARAMS_

#include <string>
#include "geometry.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std ;
using namespace cv ;

namespace params {
	enum Color { red, blue, green, yellow, violet };
	enum Shape { triangle, rectangle, polygon, circle };

	string getColorName(Color color);
	Scalar getColorRGB(Color color);

	const vector<geometry::Vector> DESTPOINTS;
	const int REACH_DIST = 15;

	const int ACC_DIST = 30;
	const int DEC_DIST = 70;

	const int SPEED = 55;
	const int minSPEED = 35;
	const int maxSPEED = 60;

	const int rotationPenalty = 35;
	const int rotationOutPenalty = 15;
	const int minRotation = 23;
	const int maxRotation = 27;
	const int rotationDuration = 50*1000;

	const vector<int> properDegrees = {0,120,-120,180,-180};
	const vector<int> safeDegrees = {0};
}

namespace exceptions {
	class NoPath {};
}

#endif