#ifndef robotic_logic_Controller_h
#define robotic_logic_Controller_h

#include<iostream>
#include<cmath>
#include<vector>
#include <unistd.h>
#include <iostream>
#include <cstdint>
//#include <boost/asio.hpp> 
#include "serial/serial.h"
#include "../Include/geometry.h"
#include "../Include/params.h"
#include "../Include/MovingObj.h"

using namespace std;

//using namespace::boost::asio;
using std::cin;
const int TIME = 1000*1000;
const int ft = 100*1000;
const double COEF = 1.0/30;
const geometry::Vector f(5,5);



class Port{
public:
	serial::Serial* port;
	Port();
	~Port();
	void fullStop();
	void writePort(vector< uint8_t > & 	data);
	void talkToSetare(int velocity, int angle, int rotation );
	bool move(vector<geometry::Vector>& path , MovingObj& agent, int& x);
	bool safeMove(vector<geometry::Vector> path , MovingObj& agent);
};

#endif


