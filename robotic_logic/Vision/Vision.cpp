#include "../Include/Vision.h"


RobotVision::~RobotVision(){
    
    camera->release();
    destroyAllWindows();
}

bool RobotVision::NewFrameIsReady()
{
	return true;
}

void RobotVision::init(){
    //in RGB
    int initialLowerBound[3] = {0,0,0} ;
    int initialUpperBound[3] = {92,92,92} ;
    lowerBound[0] = initialLowerBound[0];
    lowerBound[1] = initialLowerBound[1];
    lowerBound[2] = initialLowerBound[2];
    upperBound[0] = initialUpperBound[0];
    upperBound[1] = initialUpperBound[1];
    upperBound[2] = initialUpperBound[2];
    noiseReduction =  1 ;
    holeFilling =  1 ;
    shapeDetail = 20 ;
    objectSize = 0 ;
    brightness = 50 ;
    contrast = 50 ;
    namedWindow("trackbars") ;
    createTrackbar("contrast","trackbars",&contrast,100);
    createTrackbar("brightness","trackbars",&brightness,100);
    createTrackbar("shape detail","trackbars",&shapeDetail,100);
    createTrackbar("noise reduction","trackbars",&noiseReduction,15);
    createTrackbar("hole filling","trackbars",&holeFilling,15);
    createTrackbar("object size","trackbars",&objectSize,100);
    createTrackbar("lred","trackbars",&lowerBound[0],255);
    createTrackbar("mred","trackbars",&upperBound[0],255);
    createTrackbar("lgreen","trackbars",&lowerBound[1],255);
    createTrackbar("mgreen","trackbars",&upperBound[1],255);
    createTrackbar("lblue","trackbars",&lowerBound[2],255);
    createTrackbar("mblue","trackbars",&upperBound[2],255);
    camera = new VideoCapture(0);
}

void RobotVision::update(Field & field) {
    Mat frame ,thresh,threshMorpho,threshMorphoCopy;
    Mat kernelNoise(noiseReduction,noiseReduction,CV_8U,Scalar(1));
    Mat kernelHole(holeFilling,holeFilling,CV_8U,Scalar(1));
    vector<vector<Point> > contours;
    vector<Point> maxContour , shapePoints;
    if(!camera->isOpened()){
        cout << "camera not ready !" ;
        return ;
    }
    (*camera) >> frame ;
    frame = frame(Rect(0,50,frame.cols,350));
    frame *=pow((contrast/50.0),3);
    frame +=(brightness-50);
//    blur(frame, frame, Size(3,3));
//    resize(frame, frame, Size(0,0),0.5,0.5);
    inRange(frame, Scalar(lowerBound[2],lowerBound[1],lowerBound[0]), Scalar(upperBound[2],upperBound[1],upperBound[0]), thresh);
    morphologyEx(thresh,threshMorpho, MORPH_OPEN,kernelNoise);
    morphologyEx(threshMorpho,threshMorpho, MORPH_CLOSE,kernelHole);
    threshMorpho.copyTo(threshMorphoCopy);
    findContours(threshMorphoCopy,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE) ;
    if(contours.size() > 0){
        maxContour = contours[0];
        int maxContourArea = contourArea(maxContour);
        for(int i =0 ; i < contours.size() ; i++){
            int area = contourArea(contours[i]);
            if(area > (objectSize/2)*1000){
                if(maxContourArea < area){
                    maxContour = contours[i];
                    maxContourArea = area ;
                }
            }
        }
        if(maxContourArea > (objectSize/2)*1000){
            cout << "area of max max !" << maxContourArea << endl ;
            double arcLen = arcLength(maxContour, true);
            cout << "arcLength is :" << arcLen << endl;
            approxPolyDP(maxContour,shapePoints,(shapeDetail/200.0)*arcLen,true);
            drawContours(frame, vector<vector<Point> >(1,shapePoints),-1,Scalar(0,0,255));
            drawPoints(frame, shapePoints);
            cout << "points are : " << endl ;
            for (Point currPoint : shapePoints) {
                cout << currPoint.x << " " << currPoint.y << " , " ;
            }
            cout << endl ;
            Moments shapeMomments = moments(maxContour);
            Point centerPoint (shapeMomments.m10/shapeMomments.m00 , shapeMomments.m01/shapeMomments.m00);
            circle(frame, centerPoint, 2, Scalar(0,0,255),2);
            cout << "center point is :" << centerPoint.x << " " << centerPoint.y << endl ;
            if(shapePoints.size() == 3){
                cout << "TRIANGLE RECOGNIZED SUCCESSFULLY" << endl;
                int headPointIndex = getHeadPointIndex(shapePoints);
                Point headPoint = shapePoints[headPointIndex] ;
                Point miane = getMiane(headPointIndex, shapePoints);
                double degree = angle2(miane, headPoint);
                arrowedLine(frame, miane, headPoint, Scalar(0,255,0),2);
                ostringstream strs ;
                strs << degree ;
                String degreeString = strs.str() ;
                putText(frame,degreeString, Point(0,30), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0));

                comPath.push_back(centerPoint);

                field.agent.direction = degree ;
                field.agent.coords = pointsToGeometryVector(shapePoints);
                field.agent.COM = geometry::Vector(centerPoint.x,centerPoint.y);
                field.agent.updated = true;

                std::vector<MovingObj> obstacles;

                obstacles.push_back(MovingObj());

                {
                    geometry::Vector v(10,10);
                    std::vector<geometry::Vector> vertices;

                    vertices.push_back(geometry::Vector(300,100));
                    vertices.push_back(geometry::Vector(300,250));
                    vertices.push_back(geometry::Vector(400,100));
                    vertices.push_back(geometry::Vector(400,250));

                    obstacles[obstacles.size()-1].update(v, vertices);
                }

                field.obstacles = obstacles;

            }else{
                field.agent.direction = -1 ;
                field.agent.coords = pointsToGeometryVector(shapePoints);
                field.agent.COM = geometry::Vector(centerPoint.x,centerPoint.y);
                field.agent.updated = false;

                field.agent.update(geometry::Vector(0,0), pointsToGeometryVector(shapePoints), -1);

                cout << "WARNIG : CAN'T RECOGNIZE TRIANGLE !" << endl;
            }
            

            
        }
    }
    drawPoints(frame, points);
    drawContours(frame, vector<vector<Point> >(1,comPath),-1,Scalar(255,255,255));

    imshow("trackbars",NULL);
    imshow("frame",frame);
    imshow("hreshOrig",thresh);
    imshow("threshMorpho", threshMorpho);
}

void RobotVision::drawPoints(Mat &frame, vector<Point> points){
    for (Point currPoint : points) {
        circle(frame, currPoint, 2, Scalar(0,0,255),2);
    }
}

vector<geometry::Vector> RobotVision::pointsToGeometryVector(vector<Point> points){
    vector<geometry::Vector> results;
    for (int i=0; i<points.size(); i++) {
        results.push_back(geometry::Vector(points[i].x,points[i].y));
    }
    return results ;
}

void RobotVision::showPoints(vector<geometry::Vector> newPoints){
    for (int i = 0; i < newPoints.size(); i++) {
        points.push_back(Point(newPoints[i].x,newPoints[i].y));
    }

    return;
}

double angle2(Point point1,Point point2){
    return toDegree(atan2(point1.y - point2.y, point1.x - point2.x));
}

double angle3(Point point1,Point centerPoint,Point point2){
    double P12 = sqrt( pow( (point1.x-point2.x) , 2) + pow( (point1.y-point2.y) , 2) ) ;
    double P1c = sqrt( pow( (point1.x-centerPoint.x) , 2) + pow( (point1.y-centerPoint.y) , 2) ) ;
    double P2c = sqrt( pow( (point2.x-centerPoint.x) , 2) + pow( (point2.y-centerPoint.y) , 2) ) ;
    double radian = acos( (pow(P1c,2) + pow(P2c,2) - pow(P12,2)) / (2*P2c*P1c) );
    return toDegree(radian) ;
    
}

int getHeadPointIndex(vector<Point> points){
    double degree1 = angle3(points[0],points[1],points[2]);
    double degree2 = angle3(points[1],points[2],points[0]);
    double degree3 = angle3(points[2],points[0],points[1]);
    if(degree1 <= degree2 && degree1 <= degree3) {
        return 1 ;
    }
    else if(degree2 <= degree1 && degree2 <= degree3) {
        return 2 ;
    }
    else {
        return 0 ;
    }
}

Point getMiane(int headPointIndex,vector<Point> points){
    vector<Point> otherPoints;
    for (int i =0 ; i < 3 ; i++) {
        if(i!=headPointIndex) {
            otherPoints.push_back(points[i]);
        }
    }
    Point point1 = otherPoints[0] ;
    Point point2 = otherPoints[1] ;
    double x = ( point1.x + point2.x )/2 ;
    double y = ( point1.y + point2.y )/2 ;
    return Point(x , y) ;
    
}

double toDegree(double radian){
    return (radian/M_PI)*180 ;
}




