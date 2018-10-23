#include "../Include/Controller.h"


Port::Port(){
	port = new serial::Serial("/dev/tty.Setareh-DevB", 38400);
}

Port::~Port(){
	fullStop();
	delete port;
}

bool Port::safeMove(geometry::Vector destination , MovingObj& agent, bool& rotating) {
	// calculate speed
	int sendSpeed = params::safeSPEED;
	int dist = (destination - agent.COM).size();
	
	if (dist <= params::DEC_DIST) {
		// obey target point rules
		if(dist <= params::REACH_DIST) {
			fullStop();
			return false;
		}

		sendSpeed = ((params::safeSPEED - params::minSPEED) * (dist-10) / params::DEC_DIST) + params::minSPEED;
	} 
	// else {
	// 	// obey origin point rules
	// 	sendSpeed = ((params::safeSPEED - speedAtPrev) * (distToPrev+10) / params::DEC_DIST) + speedAtPrev;
	// }

	// calculate angle
	geometry::Vector sendV = (destination - agent.COM);
	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;
	int angle =  sendV.angle() - fixedDirection;

	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;

	if (abs(angle) > params::rotationPenalty || (rotating && abs(angle) > params::rotationOutPenalty) ) {
		cout << "$$$$$$$$$$$" <<  angle << endl;
		sendSpeed = 0;
		angle = angle / 3.0;
		angle = (abs(angle)/angle) * max(abs(angle), params::minRotation);
		angle = (abs(angle)/angle) * min(abs(angle), params::maxRotation);
		rotating = true;
	}
	else rotating = false;
	
	// cout << "COM: " << agent.COM << " -path: " << path[path.size()-1] << " -border: " << (path[path.size()-1] - agent.COM).size()<< endl;
	// cout << "DIR: " << fixedDirection << " -angle: " << (path[index] - agent.COM).angle() << " -drive: " << angle << endl; 
	// cout << "SPEED: " << sendSpeed << endl;

	// if (sendSpeed != 0) sendSpeed = 100;
	talkToSetare(sendSpeed , 0 , angle*1);
	if (rotating) {
		usleep(params::rotationDuration);
		fullStop();
	}

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

	vx = sin((90.0-angle)/180*3.14);
	vy = cos((90.0-angle)/180*3.14);

	m1 = (vy-vx*sqrt(3)+rotation/100.0) / 3;
	m2 = (-2*vy + rotation/100.0) / 3;
	m3 = (vy+vx*sqrt(3)+rotation/100.0) / 3;

	float e = max(abs(m1*1000), max(abs(m2*1000), abs(m3*1000))) / 1000.0;

	m1 = (velocity/100.0)*((m1/e) * 255);
	m2 = (velocity/100.0)*((m2/e) * 255);
	m3 = (velocity/100.0)*((m3/e) * 255);
	m4 = 0;

	if (velocity == 0) {
		m1 = (rotation/100.0)*255;
		m2 = (rotation/100.0)*255;
		m3 = (rotation/100.0)*255;
	}

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

	vector<uint8_t> data;
	data.push_back((uint8_t)115);
	data.push_back((uint8_t)abs(m1));
	data.push_back((uint8_t)abs(m2));
	data.push_back((uint8_t)abs(m3));
	data.push_back((uint8_t)abs(m4));
	data.push_back((uint8_t)A);
	writePort(data);
	
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

bool Port::move(vector<geometry::Vector>& path, vector<int>& pathSpeeds, MovingObj& agent, int& index, bool& rotating) {
	if(index < 0){
		fullStop();
		return false;
	}


	// calculate speed
	// bool fullStop = false;
	

	int sendSpeed = params::SPEED;
	int distToNext = index >= 0 && index < path.size() ? 
		(agent.COM - path[index]).size() : std::numeric_limits<int>::max();
	int distToPrev = index-1 >= 0 && index-1 < path.size() ? 
		(agent.COM - path[index-1]).size() : std::numeric_limits<int>::max();
	int speedAtPrev = index-1 >= 0 && index-1 < path.size() ? pathSpeeds[index-1] : 0;

	if(index == 0 && distToNext <= 50){
		fullStop();
		return false;
	}

	if (distToNext <= distToPrev) {
		// obey target point rules
		if(distToNext <= params::REACH_DIST) {
			index--;
			fullStop();
			// usleep(500*1000);
			return move(path, pathSpeeds, agent, index, rotating);
		}

		if(distToNext <= params::DEC_DIST) {
			if (pathSpeeds[index] == -1) {
				sendSpeed = params::minSPEED;
				fullStop();
			}
			else sendSpeed = ((params::SPEED - pathSpeeds[index]) * (distToNext-10) / params::DEC_DIST) + pathSpeeds[index];
		}
	} 
	else {
		// obey origin point rules
		if(distToPrev <= params::ACC_DIST) {
			sendSpeed = ((params::SPEED - speedAtPrev) * (distToPrev+10) / params::DEC_DIST) + speedAtPrev;
		}
	}

	sendSpeed = max(sendSpeed, params::minSPEED);
	sendSpeed = min(sendSpeed, params::maxSPEED);

	// calculate angle
	geometry::Vector sendV = (path[index] - agent.COM);
	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;
	int angle =  sendV.angle() - fixedDirection;

	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;

	int way = params::properDegrees[0];
	for(int i = 0; i < params::properDegrees.size(); i++) {
		if (abs(angle - params::properDegrees[i]) < abs(angle - way))
			way = params::properDegrees[i];
	}

	if (way == -180) way = 180;

	angle -= way;
	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;

	if (abs(angle) > params::rotationPenalty || (rotating && abs(angle) > params::rotationOutPenalty) ) {
		cout << "$$$$$$$$$$$" <<  angle << endl;
		sendSpeed = 0;
		angle = angle / 3.0;
		angle = (abs(angle)/angle) * max(abs(angle), params::minRotation);
		angle = (abs(angle)/angle) * min(abs(angle), params::maxRotation);
		rotating = true;
	}
	else rotating = false;
	
	// cout << "WAY: " << way << endl;
	// cout << "COM: " << agent.COM << " -path: " << path[path.size()-1] << " -border: " << (path[path.size()-1] - agent.COM).size()<< endl;
	// cout << "DIR: " << fixedDirection << " -angle: " << (path[index] - agent.COM).angle() << " -drive: " << angle << endl; 
	// cout << "SPEED: " << sendSpeed << endl;

	// if (sendSpeed != 0) sendSpeed = 100;
	talkToSetare(sendSpeed , way , angle*1);
	if (rotating) {
		usleep(params::rotationDuration);
		fullStop();
	}

	return true;
}


void preprocessPath(vector<geometry::Vector>& path, vector<int>& pathSpeeds) {
	pathSpeeds.clear();

	pathSpeeds.push_back(0);


	for(int i=0 ; i<path.size() ; i++){
		int x , y;
		x = max(params::xMinBound , path[i].x);  
		x = min(params::xMaxBound , path[i].x);
		y = max(params::yMinBound , path[i].y);  
		y = min(params::yMaxBound , path[i].y);
		path[i] = geometry::Vector(x,y);
	} 

	for(int i = 2; i < path.size()-1; i++) {
		geometry::Vector seg1 = path[i-1] - path[i-2];
		geometry::Vector seg2 = path[i] - path[i-1];

		int degree = abs(seg2.angle() - seg1.angle());

		pathSpeeds.push_back(params::minSPEED);
	}

	pathSpeeds.push_back(0);
}
