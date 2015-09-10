#include "../Include/Controller.h"

void moveFree(vector< geometry::Vector > path , geometry::Vector vel,serial_port* port){
	int v=45;
	//for(v=0 ; v<60 ; v+=20)
	 // talkToSetare(v,0,0,port);
	talkToSetare(v,0,0,port);
	for(int i=1 ; i<path.size() ; i++){
		geometry::Vector currP = path[i]-path[i-1];
		int angle = geometry::angleDiff(currP-vel,vel);
		int t = TIME*COEF*currP.size()/v;
		int r = 0;
		//if(i==path.size()-1)
		//  r=angle;
		talkToSetare(v,angle,r,port);
		usleep(t);
	}
	//usleep(100000);
	// fullStop();
	return;
}

void moveWithObs(vector< geometry::Vector > path , geometry::Vector vel){
	// int v;
	// geometry::Vector lastP = vel;
	// for(v=0 ; v<80 ; v++)
	//   talkToSetare(v,0,0); 
	// if(path.size()==0)
	//   return;
	// geometry::Vector currP = path[1]-path[0];
	// int angle = geometry::angleDiff(vel , currP);
	// int t = TIME*COEF*currP.size()/v;
	// int r=angle;
	// talkToSetare(v,angle,r);
	// usleep(t);
	// lastP=currP;
	// for(int i=2 ; i<path.size() ; i++){
	//   geometry::Vector currP = path[i]-path[i-1];
	//   angle = 0; 
	//   t = TIME*COEF*currP.size()/v;
	//   r=geometry::angleDiff(lastP , currP);
	//   talkToSetare(v,angle,r);
	//   usleep(t);
	//   lastP=currP;
	// }
	return;
}

serial_port* openPort(){
	const char *PORT = "/dev/tty.Setareh-DevB";
	serial_port_base::baud_rate BAUD(38400);
	serial_port_base::character_size C_SIZE( 8 );

	serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
	serial_port_base::parity PARITY( serial_port_base::parity::even );
	serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );
	io_service io;
	serial_port* port = new serial_port( io, PORT );
	port->set_option( BAUD );
	port->set_option( C_SIZE );
	port->set_option( PARITY );
	return port ;
}

void talkToSetare(int velocity, int angle, int rotation ,serial_port* port )
{
	unsigned char A = 0 ;
	float m1 , m2 , m3 , m4 ;
	m1 = 255*((-sin((45.0-angle)/180*3.14))*velocity / 100.0);
	m2 = 255*((-cos((45.0-angle)/180*3.14))*velocity / 100.0);
	m3 = -m1; //255*(( sin((45.0-angle)/180*3.14))*velocity / 100.0);
	m4 = -m2; //255*(( cos((45.0-angle)/180*3.14))*velocity / 100.0);
	int e1 = 255 - abs(m1);
	int e2 = 255 - abs(m2);
	float x = (1.0*e1)/(e1 + e2) ;
	m1 += ((     x *rotation)/100.0)*255 ;
	m2 += (((1 - x)*rotation)/100.0)*255;
	m3 += ((     x *rotation)/100.0)*255;
	m4 += (((1 - x)*rotation)/100.0)*255;
	m1 = floor(m1);
	m2 = floor(m2);
	m3 = floor(m3);
	m4 = floor(m4);

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

	writePort(115,port);
	writePort((int)abs(m1),port);
	writePort((int)abs(m2),port);
	writePort((int)abs(m3),port);
	writePort((int)abs(m4),port);
	writePort((int)abs(A),port);

	return;
}

void writePort(int input, serial_port* port){
	unsigned char command[1] = {0};
	command[0] = static_cast<unsigned char>(input);
	write( *port, buffer( command, 1 ) );
	port->send_break();

	return;
}
