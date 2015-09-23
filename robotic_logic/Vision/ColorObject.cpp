#include "../Include/ColorObject.h"

// #define __VISION_DEBUG__

ColorObject::ColorObject(params::Color color/*,int lowerBound[3],int upperBound[3],int noiseReduction ,int holeFilling , int shapeDetail , int objectSizeMin ,int objectSizeMax*/)
{
	//in RGB
	this->color = color ;
	// int i =0 ;
	// for(int item : lowerBound){
	// 	this->lowerBound[i] = item ;
	// 	i++;
	// }
	// i =0 ;
	// for(int item : upperBound){
	// 	this->upperBound[i] = item ;
	// 	i++;
	// }

	this->lowerBound = (int*)malloc(sizeof(int)*3);
	this->upperBound = (int*)malloc(sizeof(int)*3);
	this->noiseReduction = (int*)malloc(sizeof(int)*1);
	this->holeFilling = (int*)malloc(sizeof(int)*1);
	this->shapeDetail = (int*)malloc(sizeof(int)*1);
	this->objectSizeMin = (int*)malloc(sizeof(int)*1);
	this->objectSizeMax = (int*)malloc(sizeof(int)*1);
	
	*(this->lowerBound+0) = 0;
	*(this->lowerBound+1) = 0;
	*(this->lowerBound+2) = 0;

	*(this->upperBound+0) = 255;
	*(this->upperBound+1) = 255;
	*(this->upperBound+2) = 255;

	// for(int i =0 ;i < 3 ;i++){
	// 	*(this->lowerBound + i) = lowerBound[i] ;
	// 	*(this->upperBound + i) = upperBound[i] ;
	// }
	// *(this->noiseReduction) =  noiseReduction;
	// *(this->holeFilling) =  holeFilling ;
	// *(this->shapeDetail) = shapeDetail ;
	// *(this->objectSizeMin) = objectSizeMin ;
	// *(this->objectSizeMax) = objectSizeMax ;

	*(this->noiseReduction) =  1;
	*(this->holeFilling) =  1 ;
	*(this->shapeDetail) = 20 ;
	*(this->objectSizeMin) = 0 ;
	*(this->objectSizeMax) = 100 ;

	this->colorRGB = getColorRGB(this->color);

	contrast = 50;
	brightness = 50;

	ifstream initFile (getColorName(this->color)+".txt");
	if (initFile.is_open()) {
		initFile >> *(this->lowerBound+0) >> *(this->lowerBound+1) >> *(this->lowerBound+2);
		initFile >> *(this->upperBound+0) >> *(this->upperBound+1) >> *(this->upperBound+2);
		initFile >> *(this->noiseReduction);
		initFile >> *(this->holeFilling);
		initFile >> *(this->shapeDetail);
		initFile >> *(this->objectSizeMin);
		initFile >> *(this->objectSizeMax);
		initFile >> brightness >> contrast;

		cout << getColorName(this->color)+".txt" << " read." << endl;

		initFile.close();
	}

	return;
}

Color ColorObject::getColor(){
	return color ;
}

vector<MovingObj> ColorObject::findObjects(Mat originalFrame , Mat paintingFrame){
	Mat frame;
	originalFrame.copyTo(frame);
	frame *=pow((contrast/50.0),1.2);
	frame +=(brightness-50);
	cvtColor(frame, frame, CV_BGR2HSV);
	
	#ifdef __VISION_DEBUG__
	cout << getColorName(color) <<" lower bound :" <<lowerBound[0]<<" "<< lowerBound[1] << " " << lowerBound[2]<< " " << endl ;
	cout << getColorName(color) <<" upper bound :" <<upperBound[0]<<" "<< upperBound[1] << " " << upperBound[2]<< " " << endl ;
	#endif

	vector<MovingObj> objects ;
	Mat thresh,threshMorpho,threshMorphoCopy;
	Mat kernelNoise(*noiseReduction,*noiseReduction,CV_8U,Scalar(1));
	Mat kernelHole(*holeFilling,*holeFilling,CV_8U,Scalar(1));

	vector<vector<Point> > contours;
	vector<Point> maxContour , shapePoints;
	inRange(frame, Scalar(lowerBound[2],lowerBound[1],lowerBound[0]), Scalar(upperBound[2],upperBound[1],upperBound[0]), thresh);
	// threshold(frame, thresh, lowerBound[0] , upperBound[0], THRESH_BINARY);
	morphologyEx(thresh,threshMorpho, MORPH_OPEN,kernelNoise);
	morphologyEx(threshMorpho,threshMorpho, MORPH_CLOSE,kernelHole);
	threshMorpho.copyTo(threshMorphoCopy);
	findContours(threshMorphoCopy,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
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
			// cout << "area of max max !" << maxContourArea << endl ;
			double arcLen = arcLength(maxContour, true);
			//cout << "arcLength is :" << arcLen << endl;
			approxPolyDP(maxContour,shapePoints,(*shapeDetail/200.0)*arcLen,true);
			// drawContours(paintingFrame, vector<vector<Point> >(1,shapePoints),-1,getColorRGB(color));
			drawPoints(paintingFrame, shapePoints, getColorRGB(color));

			#ifdef __VISION_DEBUG__
			cout << getColorName(color) << " shape points are : " << endl ;
			for (Point currPoint : shapePoints) {
				cout << currPoint.x << " " << currPoint.y << " , " ;
			}
			cout << endl ;
			#endif

			Moments shapeMomments = moments(maxContour);
			Point centerPoint (shapeMomments.m10/shapeMomments.m00 , shapeMomments.m01/shapeMomments.m00);
			cv::circle(paintingFrame, centerPoint, 2,getColorRGB(color),2);

			#ifdef __VISION_DEBUG__
			cout << getColorName(color) << " shape center point is :" << centerPoint.x << " " << centerPoint.y << endl ;
			#endif

			MovingObj currObject ;
			currObject.COM = geometry::Vector(centerPoint.x,centerPoint.y);
			currObject.color = this->getColor();
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
					
					// std::vector<MovingObj> obstacles;
					// obstacles.push_back(MovingObj());

					// {
					//     geometry::Vector v(10,10);
					//     std::vector<geometry::Vector> vertices;

					//     vertices.push_back(geometry::Vector(300,100));
					//     vertices.push_back(geometry::Vector(300,250));
					//     vertices.push_back(geometry::Vector(400,100));
					//     vertices.push_back(geometry::Vector(400,250));

					//     obstacles[obstacles.size()-1].update(v, vertices);
					// }

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
	// imshow(getColorName(this->color), threshMorpho);
	return objects ;
}

vector<geometry::Vector> ColorObject::pointsToGeometryVector(vector<Point> points){
	vector<geometry::Vector> results;
	for (int i=0; i<points.size(); i++) {
		results.push_back(geometry::Vector(points[i].x,points[i].y));
	}
	return results ;
}

void onMouse(int event, int x, int y, int flag, void *p) {
	if(event != CV_EVENT_LBUTTONDOWN){
		p = NULL;
		return;
	}

	Vec3b data = static_cast<ColorObject*>(p)->tmpFrame.at<Vec3b>(y, x);
	int h = data.val[0];
	int s = data.val[1];
	int v = data.val[2];
	cout << "HSV: " << h << " " << s << " " << v << endl;
	*(static_cast<ColorObject*>(p)->lowerBound+0) = h - 40;
	*(static_cast<ColorObject*>(p)->lowerBound+1) = 0;
	*(static_cast<ColorObject*>(p)->lowerBound+2) = 0;
	*(static_cast<ColorObject*>(p)->upperBound+0) = h + 30;
	*(static_cast<ColorObject*>(p)->upperBound+1) = 255;
	*(static_cast<ColorObject*>(p)->upperBound+2) = 255;
}

void ColorObject::set(VideoCapture* camera) {
	Mat frame, thresh, threshMorpho;
	string colorName = getColorName(this->color);

	Mat kernelNoise(*noiseReduction,*noiseReduction,CV_8U,Scalar(1));
	Mat kernelHole(*holeFilling,*holeFilling,CV_8U,Scalar(1));

	namedWindow(colorName);
	createTrackbar("shape detail",colorName,this->shapeDetail,100);
	createTrackbar("noise reduction",colorName,this ->noiseReduction,15);
	createTrackbar("hole filling",colorName,this->holeFilling,15);
	createTrackbar("object size min",colorName,this->objectSizeMin,100);
	createTrackbar("object size max",colorName,this->objectSizeMax,100);
	createTrackbar("minHue",colorName,&(this->lowerBound[0]),360);
	createTrackbar("maxHue",colorName,&(this->upperBound[0]),360);
	createTrackbar("minSat",colorName,&(this->lowerBound[1]),255);
	createTrackbar("maxSat",colorName,&(this->upperBound[1]),255);
	createTrackbar("minVal",colorName,&(this->lowerBound[2]),255);
	createTrackbar("maxVal",colorName,&(this->upperBound[2]),255);
	createTrackbar("contrast",colorName,&contrast,100);
	createTrackbar("brightness",colorName,&brightness,100);

	// Point* newPoint = NULL;
	setMouseCallback(colorName, onMouse, this);
	while (true) {
		(*camera) >> frame ;
		frame = frame(Rect(CROP_X,CROP_Y,CROP_WIDTH,CROP_HEIGHT));
		frame *=pow((contrast/50.0),1.2);
		frame +=(brightness-50);
		cvtColor(frame, frame, CV_BGR2HSV);
		tmpFrame = frame;

		// Vec3b data = frame.at<Vec3b>(20, 20);
		// int h = data.val[0];
		// int s = data.val[1];
		// int v = data.val[2];
		// cout << "HSV: " << h << " " << s << " " << v << endl;


		inRange(frame, Scalar(lowerBound[2],lowerBound[1],lowerBound[0]), Scalar(upperBound[2],upperBound[1],upperBound[0]), thresh);
		// threshold(frame, thresh, lowerBound[0] , upperBound[0], THRESH_BINARY);
		morphologyEx(thresh, threshMorpho, MORPH_OPEN, kernelNoise);
		morphologyEx(threshMorpho, threshMorpho, MORPH_CLOSE, kernelHole);

		setTrackbarPos("shape detail",colorName,*(this->shapeDetail));
		setTrackbarPos("noise reduction",colorName,*(this->noiseReduction));
		setTrackbarPos("hole filling",colorName,*(this->holeFilling));
		setTrackbarPos("object size min",colorName,*(this->objectSizeMin));
		setTrackbarPos("object size max",colorName,*(this->objectSizeMax));
		setTrackbarPos("minHue",colorName,this->lowerBound[0]);
		setTrackbarPos("maxHue",colorName,this->upperBound[0]);
		setTrackbarPos("minSat",colorName,this->lowerBound[1]);
		setTrackbarPos("maxSat",colorName,this->upperBound[1]);
		setTrackbarPos("minVal",colorName,this->lowerBound[2]);
		setTrackbarPos("maxVal",colorName,this->upperBound[2]);
		setTrackbarPos("contrast",colorName,contrast);
		setTrackbarPos("brightness",colorName,brightness);

		*(this->shapeDetail) = getTrackbarPos("shape detail",colorName);
		*(this->noiseReduction) = getTrackbarPos("noise reduction",colorName);
		*(this->holeFilling) = getTrackbarPos("hole filling",colorName);
		*(this->objectSizeMin) = getTrackbarPos("object size min",colorName);
		*(this->objectSizeMax) = getTrackbarPos("object size max",colorName);
		this->lowerBound[0] = getTrackbarPos("minHue",colorName);
		this->upperBound[0] = getTrackbarPos("maxHue",colorName);
		this->lowerBound[1] = getTrackbarPos("minSat",colorName);
		this->upperBound[1] = getTrackbarPos("maxSat",colorName);
		this->lowerBound[2] = getTrackbarPos("minVal",colorName);
		this->upperBound[2] = getTrackbarPos("maxVal",colorName);
		contrast = getTrackbarPos("contrast",colorName);
		brightness = getTrackbarPos("brightness",colorName);

		cout << "$$ " << getColorName(color) <<" lower bound :" <<lowerBound[0]<<" "<< lowerBound[1] << " " << lowerBound[2]<< " " << endl ;
		cout << "$$ " << getColorName(color) <<" upper bound :" <<upperBound[0]<<" "<< upperBound[1] << " " << upperBound[2]<< " " << endl ;

		cvtColor(frame, frame, CV_HSV2BGR);
        imshow(colorName, frame) ;
        imshow(colorName+" tresh",thresh);
		imshow(colorName+" threshMorpho", threshMorpho);

		if(waitKey(33) == 27) {
			break;
		}
	}

	destroyWindow(colorName);
	destroyWindow(colorName+" tresh");
	destroyWindow(colorName+" threshMorpho");

	ofstream initFile(colorName+".txt");
	if(initFile.is_open())
	{
		initFile << *(this->lowerBound+0) << endl << *(this->lowerBound+1) << endl << *(this->lowerBound+2) << endl;
		initFile << *(this->upperBound+0) << endl << *(this->upperBound+1) << endl << *(this->upperBound+2) << endl;
		initFile << *(this->noiseReduction) << endl;
		initFile << *(this->holeFilling) << endl;
		initFile << *(this->shapeDetail) << endl;
		initFile << *(this->objectSizeMin) << endl;
		initFile << *(this->objectSizeMax) << endl;
		initFile << brightness << endl << contrast << endl;

		initFile.close();
		cout << colorName <<".txt write successfully!" <<endl ;
	}else{
		cout << "can't write!" <<endl ;
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

void drawPoints(Mat &frame, vector<Point> points,Scalar color){
	for (Point currPoint : points) {
		cv::circle(frame, currPoint, 2,color,2);
	}
}


