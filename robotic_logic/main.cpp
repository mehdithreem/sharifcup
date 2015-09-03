#include <iostream>
#include <unistd.h>
#include <time.h>
#include "./Include/geometry.h"
#include "./Include/Controller.h"
#include "./Include/MovingObj.h"

using namespace std;
using namespace geometry;

int main(){
	serial_port* port = openPort(); 
	MovingObj agent;
	vector<geometry::Vector> path ;
	geometry::Vector v1(0,0);
	path.push_back(v1);
	geometry::Vector v2(0,10);
	path.push_back(v2);
	geometry::Vector v3(10,10);
	path.push_back(v3);
	geometry::Vector v4(10,0);
	path.push_back(v4);
	geometry::Vector v5(0,0);
	path.push_back(v5);
	//geometry::Vector v6(0,0);
	//path.push_back(v6);
	geometry::Vector v7(0,10);
	path.push_back(v7);
	geometry::Vector v8(10,10);
	path.push_back(v8);
	geometry::Vector v9(10,0);
	path.push_back(v9);
	//geometry::Vector vq(0,0);
	//path.push_back(vq);
	 geometry::Vector vw(0,0);
	path.push_back(vw);
	geometry::Vector ve(0,10);
	path.push_back(ve);
	geometry::Vector vr(10,10);
	path.push_back(vr);
	geometry::Vector vt(10,0);
	path.push_back(vt);
	geometry::Vector vy(0,0);
	path.push_back(vy);
	moveFree(path , agent.velocity , port);
	talkToSetare(0,0,0,port);
//  moveFree(path , agent.velocity);
	// int speed;
	// talkToSetare(0,0,0);
	// int degree1 ,degree2,degree3,degree4  ;
	// usleep(1000000);
	// while (cin >> speed >> degree1>>degree2>>degree3>>degree4 ) {
	//
	//   talkToSetare(0,0,0);
	//   talkToSetare(speed,degree1,0);
	//   usleep(3);
	//   talkToSetare(speed,degree2,0);
	//   usleep(3);
	//   talkToSetare(speed,degree3,0);
	//   usleep(3);
	//   talkToSetare(speed,degree4,0);
	//   usleep(3);
	//
	//
	// // talkToSetare(0,0,0);
	// fullStop();
	// }


	// talkToSetare(0,0,0);
	// talkToSetare(40,0,0);
	// usleep(200);
	// talkToSetare(45,0,0);
	// usleep(200);
	// talkToSetare(speed,0,0);
	// usleep(2000*1000);

	return 0;
}
