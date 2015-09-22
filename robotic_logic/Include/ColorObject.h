#ifndef robotic_logic_ColorObject_h
#define robotic_logic_ColorObject_h

#include "../Include/MovingObj.h"
#include "../Include/Field.h"
#include "../Include/params.h"
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std ;
using namespace cv ;
using namespace params ;

class ColorObject {
public:
	Color color;
	Scalar colorRGB ;
	int* lowerBound;
	int* upperBound;
	int* noiseReduction ;
	int* holeFilling ;
	int* shapeDetail ;
	int* objectSizeMin ;
	int* objectSizeMax ;
	int contrast, brightness;
	
public:
	Mat tmpFrame;

	ColorObject(params::Color color/*,int lowerBound[3],int upperBound[3],int noiseReduction ,int holeFilling , int shapeDetail , int objectSizeMin,int objectSizeMax*/);
	Color getColor();
	vector<MovingObj> findObjects(Mat& frame, Mat& paintingFrame);
	vector<geometry::Vector> pointsToGeometryVector(vector<Point> points);
	void set(VideoCapture* camera);
};
double angle2(Point point1,Point point2);
double angle3(Point point1,Point centerPoint,Point point2);
int getHeadPointIndex(vector<Point> points);
Point getMiane(int headPointIndex,vector<Point> points);
double toDegree(double radian);
void drawPoints(Mat& frame , vector<Point> points,Scalar color);

#endif
