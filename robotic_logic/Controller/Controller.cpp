#include "../Include/Controller.h"


Port::Port(){
	port = new serial::Serial("/dev/tty.Setareh-DevB", 38400);
}

Port::~Port(){
	fullStop();
	delete port;
}


bool Port::move(vector<geometry::Vector>& path , MovingObj& agent, int& x){
	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;

	if(path.size()==0)
		return false;

	geometry::Vector sendV = (path[path.size()-1] - agent.COM);

	int limit = 20;
	int speed = 50;

	// if (path.size() == 2 || path.size() == 9) 
	// 	limit = 20;
	// 	cout << "-------------CORNER2-----------" << endl;
	// 	limit = 20;
	// 	speed = 45;
	// 	if (sendV.size() < limit) fullStop();
	// }
	// else if (path.size() == 2 || path.size() == 7) {
	// 	cout << "-------------CORNER-----------" << endl;
	// 	limit = 15;
	// 	speed = 43;
	// 	if (sendV.size() < limit) fullStop();
	// }

	// if (path.size() == 6 || path.size() == 1) {
	// 	cout << "-------------CORNER-----------" << endl;
	// 	fullStop();
	// 	// speed = 50;
	// }
	// 
	// if (path.size() == 5) {
	// 	fullStop();
	// 	// cin.ignore();
	// }

	if( (agent.COM - path[path.size()-1]).size() < limit ){//check the reverse path
		cout << "----------MOVE: point poped - path size: " << path.size() << endl;
		path.pop_back();
		if(path.size()==0)
			return false;
		x = (agent.COM - path[path.size()-1]).size();
		// fullStop();
		// cin.ignore();
		//talkToSetare(0,0,0);
		// return true;
	}
	int angle =  sendV.angle() - fixedDirection;


	// speed = ((agent.COM - path[path.size()-1]).size() * params::SPEED + x * params::minSPEED) / x;
	// // int speed = ((agent.COM - path[path.size()-1]).size() * params::SPEED) / x;
	// speed = max(speed, params::minSPEED);
	// speed = min(speed, params::maxSPEED);

	cout << "COM: " << agent.COM << " -path: " << path[path.size()-1] << " -border: " << (path[path.size()-1] - agent.COM).size()<< endl;
	cout << "DIR: " << fixedDirection << " -angle: " << (path[path.size()-1] - agent.COM).angle() << " -drive: " << angle << endl; 
	cout << "SPEED: " << speed << endl;

	// talkToSetare(0, angle , 0);
	talkToSetare(85 , angle , 0);
	return true;
}

bool Port::safeMove(vector<geometry::Vector> path , MovingObj& agent){
	int fixedDirection = agent.direction >= 0 ? agent.direction - 180 : agent.direction + 180;

	if(path.size()==0)
		return false;
	if( (agent.COM - path[path.size()-1]).size() < params::LIMITDEST ){//check the reverse path
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
	int e1 = 255 - abs(m1);
	int e2 = 255 - abs(m2);
	float x = (1.0*e1)/(e1 + e2) ;
	m1 = 255*((-sin((45.0-angle)/180*3.14))*velocity / 100.0);
	m2 = 255*((-cos((45.0-angle)/180*3.14))*velocity / 100.0);
	m3 = -m1;
	m4 = -m2;
	m1 += ((     x *rotation)/100.0)*255; m1 = floor(m1);
	m2 += (((1 - x)*rotation)/100.0)*255; m2 = floor(m2);
	m3 += ((     x *rotation)/100.0)*255; m3 = floor(m3);
	m4 += (((1 - x)*rotation)/100.0)*255;	m4 = floor(m4);

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
	cout<<"A IS ##########"<<(int)A<<endl;
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
