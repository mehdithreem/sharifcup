#include "../Include/Controller.h"


Port::Port(){
	port = new serial::Serial("/dev/tty.Setareh-DevB", 38400);
}

Port::~Port(){
	fullStop();
	delete port;
}

// bool Port::move(vector<geometry::Vector>& path , MovingObj& agent, int& x){
// 	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;

// 	if(path.size()==0)
// 		return false;

// 	geometry::Vector sendV = (path[path.size()-1] - agent.COM);

// 	int limit = 30;
// 	int speed = 50;

// 	// if (path.size() == 2 || path.size() == 9) 
// 	// 	limit = 20;
// 	// 	cout << "-------------CORNER2-----------" << endl;
// 	// 	limit = 20;
// 	// 	speed = 45;
// 	// 	if (sendV.size() < limit) fullStop();
// 	// }
// 	// else if (path.size() == 2 || path.size() == 7) {
// 	// 	cout << "-------------CORNER-----------" << endl;
// 	// 	limit = 15;
// 	// 	speed = 43;
// 	// 	if (sendV.size() < limit) fullStop();
// 	// }

// 	// if (path.size() == 6 || path.size() == 1) {
// 	// 	cout << "-------------CORNER-----------" << endl;
// 	// 	fullStop();
// 	// 	// speed = 50;
// 	// }
// 	// 
// 	// if (path.size() == 5) {
// 	// 	fullStop();
// 	// 	// cin.ignore();
// 	// }

// 	if( (agent.COM - path[path.size()-1]).size() < limit ){//check the reverse path
// 		cout << "----------MOVE: point poped - path size: " << path.size() << endl;
// 		path.pop_back();
// 		if(path.size()==0)
// 			return false;
// 		x = (agent.COM - path[path.size()-1]).size();
// 		// fullStop();
// 		// cin.ignore();
// 		talkToSetare(0,0,0);
// 		// return true;
// 	}
// 	int angle =  sendV.angle() - fixedDirection;


// 	// speed = ((agent.COM - path[path.size()-1]).size() * params::SPEED + x * params::minSPEED) / x;
// 	// // int speed = ((agent.COM - path[path.size()-1]).size() * params::SPEED) / x;
// 	// speed = max(speed, params::minSPEED);
// 	// speed = min(speed, params::maxSPEED);

// 	cout << "COM: " << agent.COM << " -path: " << path[path.size()-1] << " -border: " << (path[path.size()-1] - agent.COM).size()<< endl;
// 	cout << "DIR: " << fixedDirection << " -angle: " << (path[path.size()-1] - agent.COM).angle() << " -drive: " << angle << endl; 
// 	cout << "SPEED: " << speed << endl;

// 	// talkToSetare(0, angle , 0);
// 	talkToSetare(50 , angle , 0);
// 	return true;
// }

bool Port::safeMove(vector<geometry::Vector> path , MovingObj& agent){
	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;

	if(path.size()==0)
		return false;
	if( (agent.COM - path[path.size()-1]).size() < params::REACH_DIST ){//check the reverse path
		path.pop_back();
		if(path.size()==0)
			return false;
	}
	int rotation =  path[path.size()-1].angle() - fixedDirection;
	talkToSetare(0 , 0 , rotation);
	talkToSetare(params::SPEED , 0 , 0);
	//check for talkToSetare(params::SPEED , 0 , rotation);
	return true;
}


void Port::fullStop(){
	vector<uint8_t > data;
	data.push_back((uint8_t )115);
	data.push_back((uint8_t )255);
	data.push_back((uint8_t )255);
	data.push_back((uint8_t )255);
	data.push_back((uint8_t )255);
	data.push_back((uint8_t )255);
	writePort(data);
}

void Port::talkToSetare(int velocity, int angle, int rotation )
{
	unsigned char A = 0 ;
	float m1 , m2 , m3 , m4 ;
	// int e1 = 255 - abs(m1);
	// int e2 = 255 - abs(m2);
	// float x = (1.0*e1)/(e1 + e2) ;
	// m1 = 255*((-sin((45.0-angle)/180*3.14))*velocity / 100.0);
	// m2 = 255*((-cos((45.0-angle)/180*3.14))*velocity / 100.0);
	// m3 = -m1;
	// m4 = -m2;
	// m1 += ((     x *rotation)/100.0)*255; m1 = floor(m1);
	// m2 += (((1 - x)*rotation)/100.0)*255; m2 = floor(m2);
	// m3 += ((     x *rotation)/100.0)*255; m3 = floor(m3);
	// m4 += (((1 - x)*rotation)/100.0)*255;	m4 = floor(m4);
	
	float vx, vy;
	vx = (velocity/100.0) * sin((90.0-angle)/180*3.14);
	vy = (velocity/100.0) * cos((90.0-angle)/180*3.14);

	m1 = (vy-vx*sqrt(3)+rotation) / 3;
	m2 = (-2*vy + rotation) / 3;
	m3 = (vy+vx*sqrt(3)+rotation) / 3;

	m1 = floor(m1 * 255);
	m2 = floor(m2 * 255);
	m3 = floor(m3 * 255);
	m4 = 0;

	if(m1>0)
		A|=1<<0;
	else if(m1<0)
		A|=1<<1;

	if(m2>0)
		A|=1<<2;
	else if(m2<0)
		A|=1<<3;

	if(m3>0)
		A|=1<<4;
	else if(m3<0)
		A|=1<<5;

	if(m4>0)
		A|=1<<6;
	else if(m4<0)
		A|=1<<7;

	// m1 = ;
	// m2 = 0;
	// m3 = 255;
	// A = 18;
	
	cout << m1 << " # " << m2 << " # " << m3 << endl;

	for (int i = 0; i < 200; i += 50) {
		m1 = 254 - i;
		m2 = 0;
		m3 = -255 + i;
		A = 33;

		vector<uint8_t> data;
		data.push_back((uint8_t)115);
		data.push_back((uint8_t)abs(m1));
		data.push_back((uint8_t)abs(m2));
		data.push_back((uint8_t)abs(m3));
		data.push_back((uint8_t)abs(m4));
		data.push_back((uint8_t)A);
		writePort(data);
		usleep(50);
	}
	
	return;
}

void Port:: writePort(vector< uint8_t > & 	data){
	size_t s = 0;
	while (s < 6){
		s = port->write(data);
		// cout << "S is " << s << endl;
	}
	return;
}

// bool Port::move(vector<geometry::Vector>& path, vector<int>& pathSpeeds, MovingObj& agent, int& index) {
// 	if(index >= path.size())
// 		return false;

// 	// calculate speed
// 	bool fullStop = false;
// 	int sendSpeed = params::SPEED;
// 	int distToNext = index >= 0 && index < path.size() ? 
// 		(agent.COM - path[index]).size() : std::numeric_limits<int>::max();
// 	int distToPrev = index-1 >= 0 && index-1 < path.size() ? 
// 		(agent.COM - path[index-1]).size() : std::numeric_limits<int>::max();
// 	int speedAtPrev = index-1 >= 0 && index-1 < path.size() ? pathSpeeds[index-1] : 0;

// 	if (distToNext <= distToPrev) {
// 		// obey target point rules
// 		if(distToNext <= params::REACH_DIST) {
// 			index++;
// 			return move(path, pathSpeeds, index);
// 		}

// 		if(distToNext <= params::DEC_DIST) {
// 			if (pathSpeeds[index] == -1) {
// 				sendSpeed = params::minSPEED;
// 				fullStop();
// 			}
// 			else sendSpeed = ((params::SPEED - pathSpeeds[index]) * (distToNext-10) / params::DEC_DIST) + pathSpeeds[index];
// 		}
// 	} 
// 	else {
// 		// obey origin point rules
// 		if(distToPrev <= params::ACC_DIST) {
// 			sendSpeed = ((params::SPEED - speedAtPrev) * (distToPrev+10) / params::DEC_DIST) + speedAtPrev;
// 		}
// 	}

// 	sendSpeed = max(sendSpeed, params::minSPEED);
// 	sendSpeed = min(sendSpeed, params::maxSPEED);

// 	// calculate angle
// 	geometry::Vector sendV = (path[index] - agent.COM);
// 	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;
// 	int angle =  sendV.angle() - fixedDirection;

// 	cout << "COM: " << agent.COM << " -path: " << path[path.size()-1] << " -border: " << (path[path.size()-1] - agent.COM).size()<< endl;
// 	cout << "DIR: " << fixedDirection << " -angle: " << (path[index] - agent.COM).angle() << " -drive: " << angle << endl; 
// 	cout << "SPEED: " << speed << endl;
	
// 	talkToSetare(sendSpeed , angle , 0);
// }


// void preprocessPath(vector<geometry::Vector>& path, vector<int>& pathSpeeds) {
// 	pathSpeeds.clear();

// 	pathSpeeds.push_back(0);

// 	for(int i = 2; i < path.size()-1; i++) {
// 		geometry::Vector seg1 = path[i-1] - path[i-2];
// 		geometry::Vector seg2 = path[i] - path[i-1];

// 		int degree = math.abs(seg2.angle() - seg1.angle());

// 		pathSpeeds.push_back(params::minSPEED);
// 	}

// 	pathSpeeds.push_back(0);
// }
