#include "../Include/ColorObject.h"

ColorObject::ColorObject(params::Color color,int lowerBound[3],int upperBound[3],int noiseReduction ,int holeFilling , int shapeDetail , int objectSizeMin ,int objectSizeMax)
{
    //in RGB
    this->color = color ;
    
//    int i =0 ;
//    for(int item : lowerBound){
//        this->lowerBound[i] = item ;
//        i++;
//    }
//    i =0 ;
//    for(int item : upperBound){
//        this->upperBound[i] = item ;
//        i++;
//    }
    this->lowerBound = (int*)malloc(sizeof(int)*3);
    this->upperBound = (int*)malloc(sizeof(int)*3);
    this->noiseReduction = (int*)malloc(sizeof(int)*1);
    this->holeFilling = (int*)malloc(sizeof(int)*1);
    this->shapeDetail = (int*)malloc(sizeof(int)*1);
    this->objectSizeMin = (int*)malloc(sizeof(int)*1);
    this->objectSizeMax = (int*)malloc(sizeof(int)*1);
    
    for(int i =0 ;i < 3 ;i++){
        *(this->lowerBound + i) = lowerBound[i] ;
        *(this->upperBound + i) = upperBound[i] ;
    }
    *(this->noiseReduction) =  noiseReduction;
    *(this->holeFilling) =  holeFilling ;
    *(this->shapeDetail) = shapeDetail ;
    *(this->objectSizeMin) = objectSizeMin ;
    *(this->objectSizeMax) = objectSizeMax ;
    namedWindow(getColorName((this->color)));
    createTrackbar("shape detail",getColorName(this->color),this->shapeDetail,100);
    createTrackbar("noise reduction",getColorName(this->color),this->noiseReduction,15);
    createTrackbar("hole filling",getColorName(this->color),this->holeFilling,15);
    createTrackbar("object size min",getColorName(this->color),this->objectSizeMin,100);
    createTrackbar("object size max",getColorName(this->color),this->objectSizeMax,100);
    createTrackbar("lred",getColorName(this->color),&(this->lowerBound[0]),255);
    createTrackbar("mred",getColorName(this->color),&(this->upperBound[0]),255);
    createTrackbar("lgreen",getColorName(this->color),&(this->lowerBound[1]),255);
    createTrackbar("mgreen",getColorName(this->color),&(this->upperBound[1]),255);
    createTrackbar("lblue",getColorName(this->color),&(this->lowerBound[2]),255);
    createTrackbar("mblue",getColorName(this->color),&(this->upperBound[2]),255);
    this->colorRGB = getColorRGB(this->color);
    
}

Color ColorObject::getColor(){
    return color ;
}

vector<MovingObj> ColorObject::findObjects(Mat& frame , Mat& paintingFrame){
    *(this->shapeDetail) = getTrackbarPos("shape detail",getColorName(this->color));
    *(this->noiseReduction) = getTrackbarPos("noise reduction",getColorName(this->color));
    *(this->holeFilling) = getTrackbarPos("hole filling",getColorName(this->color));
    *(this->objectSizeMin) = getTrackbarPos("object size min",getColorName(this->color));
    *(this->objectSizeMax) = getTrackbarPos("object size max",getColorName(this->color));
    this->lowerBound[0] = getTrackbarPos("lred",getColorName(this->color));
    this->upperBound[0] = getTrackbarPos("mred",getColorName(this->color));
    this->lowerBound[1] = getTrackbarPos("lgreen",getColorName(this->color));
    this->upperBound[1] = getTrackbarPos("mgreen",getColorName(this->color));
    this->lowerBound[2] = getTrackbarPos("lblue",getColorName(this->color));
    this->upperBound[2] = getTrackbarPos("mblue",getColorName(this->color));
    
    cout << getColorName(color) <<" lower bound :" <<lowerBound[0]<<" "<< lowerBound[1] << " " << lowerBound[2]<< " " << endl ;
    cout << getColorName(color) <<" upper bound :" <<upperBound[0]<<" "<< upperBound[1] << " " << upperBound[2]<< " " << endl ;
    
    vector<MovingObj> objects ;
    Mat thresh,threshMorpho,threshMorphoCopy;
    Mat kernelNoise(*noiseReduction,*noiseReduction,CV_8U,Scalar(1));
    Mat kernelHole(*holeFilling,*holeFilling,CV_8U,Scalar(1));
    vector<vector<Point> > contours;
    vector<Point> maxContour , shapePoints;
    inRange(frame, Scalar(lowerBound[2],lowerBound[1],lowerBound[0]), Scalar(upperBound[2],upperBound[1],upperBound[0]), thresh);
//    threshold(frame, thresh, lowerBound[0] , upperBound[0], THRESH_BINARY);
    morphologyEx(thresh,threshMorpho, MORPH_OPEN,kernelNoise);
    morphologyEx(threshMorpho,threshMorpho, MORPH_CLOSE,kernelHole);
    threshMorpho.copyTo(threshMorphoCopy);
    findContours(threshMorphoCopy,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE) ;
    if(contours.size() > 0){
        maxContour = contours[0];
        int maxContourArea = contourArea(maxContour);
        for(int i =0 ; i < contours.size() ; i++){
            int area = contourArea(contours[i]);
            if(area > (*objectSizeMin/2)*1000 && area < (*objectSizeMax/2)*1000){
                if(maxContourArea < area){
                    maxContour = contours[i];
                    maxContourArea = area ;
                }
            }
        }
        if(maxContourArea > (*objectSizeMin/2)*1000 && maxContourArea < (*objectSizeMax/2)*1000){
            //            cout << "area of max max !" << maxContourArea << endl ;
            double arcLen = arcLength(maxContour, true);
            //            cout << "arcLength is :" << arcLen << endl;
            approxPolyDP(maxContour,shapePoints,(*shapeDetail/200.0)*arcLen,true);
//            drawContours(paintingFrame, vector<vector<Point> >(1,shapePoints),-1,getColorRGB(color));
            drawPoints(paintingFrame, shapePoints,getColorRGB(color));
            cout << getColorName(color) << " shape points are : " << endl ;
            for (Point currPoint : shapePoints) {
                cout << currPoint.x << " " << currPoint.y << " , " ;
            }
            cout << endl ;
            Moments shapeMomments = moments(maxContour);
            Point centerPoint (shapeMomments.m10/shapeMomments.m00 , shapeMomments.m01/shapeMomments.m00);
            cv::circle(paintingFrame, centerPoint, 2,getColorRGB(color),2);
            cout << getColorName(color) << " shape center point is :" << centerPoint.x << " " << centerPoint.y << endl ;
            MovingObj currObject ;
            currObject.COM = geometry::Vector(centerPoint.x,centerPoint.y);
            if(this->color == params::black){
                if(shapePoints.size() == 3){
                    cout << "TRIANGLE RECOGNIZED SUCCESSFULLY" << endl;
                    int headPointIndex = getHeadPointIndex(shapePoints);
                    Point headPoint = shapePoints[headPointIndex] ;
                    Point miane = getMiane(headPointIndex, shapePoints);
                    double degree = angle2(miane, headPoint);
                    arrowedLine(paintingFrame, miane, headPoint, Scalar(0,255,156),2);
                    ostringstream strs ;
                    strs << degree ;
                    String degreeString = strs.str() ;
                    putText(paintingFrame,degreeString, Point(0,30), FONT_HERSHEY_PLAIN, 1, Scalar(0,255,156));
                    
                    //                std::vector<MovingObj> obstacles;
                    //                obstacles.push_back(MovingObj());
                    //
                    //                {
                    //                    geometry::Vector v(10,10);
                    //                    std::vector<geometry::Vector> vertices;
                    //
                    //                    vertices.push_back(geometry::Vector(300,100));
                    //                    vertices.push_back(geometry::Vector(300,250));
                    //                    vertices.push_back(geometry::Vector(400,100));
                    //                    vertices.push_back(geometry::Vector(400,250));
                    //
                    //                    obstacles[obstacles.size()-1].update(v, vertices);
                    //                }
                    currObject.update(geometry::Vector(0,0), pointsToGeometryVector(shapePoints),degree);
                    
                }else{
                    currObject.update(geometry::Vector(0,0), pointsToGeometryVector(shapePoints));
                    cout << "WARNIG : CAN'T RECOGNIZE TRIANGLE !" << endl;
                }
            }else{
                currObject.update(geometry::Vector(0,0), pointsToGeometryVector(shapePoints));
            }
            objects.push_back(currObject);
        }
    }
    imshow(getColorName(this->color),thresh);
//    imshow(getColorName(this->color), threshMorpho);
    return objects ;
}

vector<geometry::Vector> ColorObject::pointsToGeometryVector(vector<Point> points){
    vector<geometry::Vector> results;
    for (int i=0; i<points.size(); i++) {
        results.push_back(geometry::Vector(points[i].x,points[i].y));
    }
    return results ;
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

void drawPoints(Mat &frame, vector<Point> points,Scalar color){
    for (Point currPoint : points) {
        cv::circle(frame, currPoint, 2,color,2);
    }
}


