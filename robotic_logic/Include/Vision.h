#ifndef robotic_logic_Vision_h
#define robotic_logic_Vision_h

#include "../Include/MovingObj.h"
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <String>
#include <cmath>

using namespace std ;
using namespace cv ;

class RobotVision {
private :
    VideoCapture* camera ;
    int lowerBound[3];
    int upperBound[3];
    int noiseReduction ;
    int holeFilling ;
    int shapeDetail ;
    int objectSize ;
public:
    ~RobotVision();
    bool NewFrameIsReady();
    void init();
    void update(/*MovingObj& ourBot , MovingObj& enemyBot , vector<MovingObj>& obstacle*/);
    void drawPoints(Mat& frame , vector<Point> points);
    
};
double angle2(Point point1,Point point2);
double angle3(Point point1,Point centerPoint,Point point2);
int getHeadPointIndex(vector<Point> points);
Point getMiane(int headPointIndex,vector<Point> points);
double toDegree(double radian);



#endif
