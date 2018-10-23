#ifndef _PARAMS_
#define _PARAMS_

#include <string>
#include "geometry.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std ;
using namespace cv ;

namespace params {
	enum Color { red, blue, green, yellow, violet, black};
	enum Shape { triangle, rectangle, polygon, circle };

	string getColorName(Color color);
	Scalar getColorRGB(Color color);

	const int CROP_X = 85;
	const int CROP_Y = 37;
	const int CROP_WIDTH = 494;
	const int CROP_HEIGHT = 404;

	const vector<geometry::Vector> DESTPOINTS;
	const int LOST_LIMIT = 70;
	const int REACH_DIST = 15;

	const int ACC_DIST = 30;
	const int DEC_DIST = 70;

	const int SPEED = 55;
	const int safeSPEED = 47;
	const int minSPEED = 35;
	const int maxSPEED = 60;

	const int rotationPenalty = 35;
	const int rotationOutPenalty = 15;
	const int minRotation = 23;
	const int maxRotation = 27;
	const int rotationDuration = 50*1000;

	const vector<int> properDegrees = {0,120,-120,180,-180};
	const vector<int> safeDegrees = {0};

	const int xMinBound = 50;
	const int yMinBound = 50;
	const int xMaxBound = 450;
	const int yMaxBound = 250;

	const int xInfinity = 1000*10;
	const int yInfinity = 1000*10;
	const int MinesXInfinity = -1000*10;
	const int yMinesInfinity = -1000*10;
}

namespace exceptions {
	class NoPath {};
}

#endif