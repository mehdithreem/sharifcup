#ifndef robotic_logic_Vision_h
#define robotic_logic_Vision_h

#include "../Include/MovingObj.h"
#include "../Include/Field.h"
#include "../Include/ColorObject.h"
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <String>
#include <cmath>

using namespace std ;
using namespace cv ;

class RobotVision {
public :
	int contrast , brightness ;    
	VideoCapture* camera ;
	vector<ColorObject> colorObjects ;
	Mat* currFrame ;
	vector<Point> points;
    vector<Point> comPath;
    
public:
	~RobotVision();
	bool NewFrameIsReady();
	void init();
	void update(Field& field , bool type);
	void set();

	void drawPoints(Mat& frame , vector<Point> points);
    void showPoints(vector<geometry::Vector> newPoints);
};


#endif
