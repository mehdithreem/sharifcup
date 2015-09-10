#ifndef robotic_logic_Controller_h
#define robotic_logic_Controller_h

#include<iostream>
#include<cmath>
#include<vector>
#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp> 
#include "../Include/geometry.h"
using namespace std;

using namespace::boost::asio;
using std::cin;
const int TIME = 1000*1000;
const int ft = 100*1000;
const double COEF = 1.0/30;
const geometry::Vector f(5,5);



class Port{
public:
	serial_port* port;
	Port();
	~Port();
	void fullStop();
	void writePort(int input);
	void talkToSetare(int velocity, int angle, int rotation ,serial_port* port );
};

#endif


