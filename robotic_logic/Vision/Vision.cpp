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

void RobotVision::init(){
    string line,colorName;
    
    //black
    int lowBlack[3] = {0,0,0};
    int upBlack[3] = {75,80,90};
    int noiseBlack = 1;
    int holeBlack = 1;
    int detailBlack = 20;
    int sizeMinBlack = 0;
    int sizeMaxBlack = 100;
    //blue
    int lowBlue[3] = {0,0,0};
    int upBlue[3] = {0,0,0};
    int noiseBlue = 1;
    int holeBlue = 1;
    int detailBlue = 20;
    int sizeMinBlue = 0;
    int sizeMaxBlue = 100;
    //red
    int lowRed[3] = {0,0,0};
    int upRed[3] = {0,0,0};
    int noiseRed = 1 ;
    int holeRed = 1;
    int detailRed = 20;
    int sizeMinRed = 0;
    int sizeMaxRed = 100;
    //green
    int lowGreen[3] = {0,0,0};
    int upGreen[3] {0,0,0};
    int noiseGreen = 1;
    int holeGreen = 1;
    int detailGreen = 20;
    int sizeMinGreen = 0;
    int sizeMaxGreen = 100;
    //yellow
    int lowYellow[3] ={0,0,0};
    int upYellow[3] ={0,0,0};
    int noiseYellow = 1;
    int holeYellow = 1;
    int detailYellow = 20;
    int sizeMinYellow = 0;
    int sizeMaxYellow = 100;
    //violet
    int lowViolet[3] ={0,0,0};
    int upViolet[3] ={0,0,0};
    int noiseViolet = 1;
    int holeViolet = 1;
    int detailViolet = 20;
    int sizeMinViolet = 0;
    int sizeMaxViolet = 100;
    
    
    
    brightness = 50 ;
    contrast = 50 ;
    namedWindow("frame") ;
    createTrackbar("contrast","frame",&contrast,100);
    createTrackbar("brightness","frame",&brightness,100);
    camera = new VideoCapture(0);
    
    
    
    ifstream initFile ("init.txt");
    if (initFile.is_open())
    {
        cout << "file exist !" << endl;
        initFile >> colorName >> lowBlack[0] >> lowBlack[1] >> lowBlack[2] >> upBlack[0] >> upBlack[1] >> upBlack[2] >> noiseBlack >> holeBlack >> detailBlack >> sizeMinBlack >> sizeMaxBlack ;
        
        initFile >> colorName >> lowBlue[0] >> lowBlue[1] >> lowBlue[2] >> upBlue[0] >> upBlue[1] >> upBlue[2] >> noiseBlue >> holeBlue >> detailBlue >> sizeMinBlue >> sizeMaxBlue ;
        
        initFile >> colorName >> lowRed[0] >> lowRed[1] >> lowRed[2] >> upRed[0] >> upRed[1] >> upRed[2] >> noiseRed >> holeRed >> detailRed >> sizeMinRed >> sizeMaxRed ;
        
        initFile >> colorName >> lowGreen[0] >> lowGreen[1] >> lowGreen[2] >> upGreen[0] >> upGreen[1] >> upGreen[2] >> noiseGreen >> holeGreen >> detailGreen >> sizeMinGreen >> sizeMaxGreen ;
        
        initFile >> colorName >> lowYellow[0] >> lowYellow[1] >> lowYellow[2] >> upYellow[0] >> upYellow[1] >> upYellow[2] >> noiseYellow >> holeYellow >> detailYellow >> sizeMinYellow >> sizeMaxYellow ;
        
        initFile >> colorName >> lowViolet[0] >> lowViolet[1] >> lowViolet[2] >> upViolet[0] >> upViolet[1] >> upViolet[2] >> noiseViolet >> holeViolet >> detailViolet >> sizeMinViolet >> sizeMaxViolet ;
    }
    initFile.close();
    colorObjects.push_back(ColorObject(params::black, lowBlack, upBlack, noiseBlack, holeBlack, detailBlack, sizeMinBlack,sizeMaxBlack));
    colorObjects.push_back(ColorObject(params::blue, lowBlue, upBlue, noiseBlue, holeBlue, detailBlue, sizeMinBlue,sizeMaxBlue));
    colorObjects.push_back(ColorObject(params::red, lowRed , upRed, noiseRed, holeRed, detailRed, sizeMinRed,sizeMaxRed));
    colorObjects.push_back(ColorObject(params::green, lowGreen, upGreen, noiseGreen, holeGreen, detailGreen, sizeMinGreen,sizeMaxGreen));
    colorObjects.push_back(ColorObject(params::yellow, lowYellow, upYellow, noiseYellow, holeYellow, detailYellow, sizeMinYellow,sizeMaxYellow));
    colorObjects.push_back(ColorObject(params::violet, lowViolet, upViolet, noiseViolet, holeViolet, detailViolet, sizeMinViolet,sizeMaxViolet));
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
    frame = frame(Rect(85,37,494,404));
    frame *=pow((contrast/50.0),3);
    frame +=(brightness-50);
    
    //    blur(frame, frame, Size(3,3));
    //    resize(frame, frame, Size(0,0),0.5,0.5);
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
                vector<MovingObj> currObjects ;
                currObjects = colorObjects[0].findObjects(frame,*(this->currFrame));
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
            }
            
        }
    }else{
        colorObjects[0].findObjects(frame,*(this->currFrame));
    }
    field.rival = rival ;
    field.obstacles = obstacles ;
    imshow("frame",*(this->currFrame));
}

void RobotVision::showPoints(vector<Point> points,Scalar color){
    for (Point currPoint : points) {
        cv::circle(*(this->currFrame), currPoint, 2,color,2);
    }
    imshow("frame", *(this->currFrame)) ;
}







