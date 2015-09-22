#include "../Include/Vision.h"


RobotVision::~RobotVision(){
	
	camera->release();
	destroyAllWindows();
	ofstream initFile("init.txt");
	if(initFile.is_open())
	{
		for (ColorObject currColorObject : colorObjects) {
			initFile << getColorName(currColorObject.getColor()) << "\n" << currColorObject.lowerBound[0] << " " << currColorObject.lowerBound[1] << " " << currColorObject.lowerBound[2] << "\n" ;
			initFile << currColorObject.upperBound[0] << " " << currColorObject.upperBound[1] << " " << currColorObject.upperBound[2] << "\n" ;
			initFile << currColorObject.noiseReduction << "\n" <<currColorObject.holeFilling << "\n" <<currColorObject.shapeDetail << "\n" <<currColorObject.objectSizeMin << "\n" <<currColorObject.objectSizeMax ;
		}
		cout << "write successfully !" <<endl ;
	}else{
		cout << "can't write !" <<endl ;
	}
}

bool RobotVision::NewFrameIsReady()
{
	return true;
}

void RobotVision::init() {
	string line,colorName;
	
	// brightness = 50 ;
	// contrast = 50 ;
	namedWindow("frame") ;
	// createTrackbar("contrast","frame",&contrast,100);
	// createTrackbar("brightness","frame",&brightness,100);
	camera = new VideoCapture(0);
	
	colorObjects.push_back(ColorObject(params::black/*, lowBlack, upBlack, noiseBlack, holeBlack, detailBlack, sizeMinBlack,sizeMaxBlack*/));
	colorObjects.push_back(ColorObject(params::blue/*, lowBlue, upBlue, noiseBlue, holeBlue, detailBlue, sizeMinBlue,sizeMaxBlue*/));
	colorObjects.push_back(ColorObject(params::red/*, lowRed , upRed, noiseRed, holeRed, detailRed, sizeMinRed,sizeMaxRed*/));
	colorObjects.push_back(ColorObject(params::green/*, lowGreen, upGreen, noiseGreen, holeGreen, detailGreen, sizeMinGreen,sizeMaxGreen*/));
	colorObjects.push_back(ColorObject(params::yellow/*, lowYellow, upYellow, noiseYellow, holeYellow, detailYellow, sizeMinYellow,sizeMaxYellow*/));
	colorObjects.push_back(ColorObject(params::violet/*, lowViolet, upViolet, noiseViolet, holeViolet, detailViolet, sizeMinViolet,sizeMaxViolet*/));
}

void RobotVision::set() {
	for(int i = 0; i < colorObjects.size(); i++) {
		colorObjects[i].set(camera);
	}
}

void RobotVision::update(Field & field,bool type) {
	vector<MovingObj> obstacles ;
	MovingObj agent ,rival ;
	Mat frame ;

	if(!camera->isOpened()){
		cout << "camera not ready !" ;
		return ;
	}

	(*camera) >> frame ;
	frame = frame(Rect(CROP_X,CROP_Y,CROP_WIDTH,CROP_HEIGHT));
	
	//blur(frame, frame, Size(3,3));
	//resize(frame, frame, Size(0,0),0.5,0.5);
	this->currFrame = &frame ;

	if(type){
		for (ColorObject currColorObject : colorObjects) {
			vector<MovingObj> currObjects ;
			currObjects = currColorObject.findObjects(frame,*(this->currFrame));
			if(currColorObject.getColor() == params::black){
				if(currObjects.empty()){
					cout << "CAN'T RECOGNIZE ROBOT AT ALL !" << endl ;
					field.agent = MovingObj() ;
					field.agent.updated = false ;
				}else{
					field.agent = currObjects[0];
					if(field.agent.coords.size() == 3){
						field.agent.updated = true ;
					}else{
						field.agent.updated = false ;
					}
				}
			}else{
				for(MovingObj currObject : currObjects){
					obstacles.push_back(currObject);
				}
			}
			
		}
		field.obstacles = obstacles ;
	}else{
		vector<MovingObj> currObjects ;
		currObjects = colorObjects[0].findObjects(frame,*(this->currFrame));
		if(currObjects.empty()){
			cout << "CAN'T RECOGNIZE ROBOT AT ALL !" << endl ;
			field.agent = MovingObj() ;
			field.agent.updated = false ;
		}else{
			field.agent = currObjects[0];
			if(field.agent.coords.size() == 3){
				comPath.push_back(Point(field.agent.COM.x, field.agent.COM.y));
				field.agent.updated = true ;
			}else{
				field.agent.updated = false ;
			}
		}        
	}
	field.rival = rival ;

	drawPoints(*(this->currFrame), points);
	drawContours(*(this->currFrame), vector<vector<Point> >(1,comPath),-1,Scalar(255,255,255));
	imshow("frame",*(this->currFrame));
}

void RobotVision::showPoints(vector<geometry::Vector> newPoints){
	for (int i = 0; i < newPoints.size(); i++) {
		points.push_back(Point(newPoints[i].x,newPoints[i].y));
	}

	return;
}

void RobotVision::drawPoints(Mat &frame, vector<Point> points){
	for (Point currPoint : points) {
		cv::circle(frame, currPoint, 2, Scalar(0,0,255),2);
	}
}



