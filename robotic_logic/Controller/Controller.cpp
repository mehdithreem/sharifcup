#include "../Include/Controller.h"


Port::Port(){
	const char *PORT = "/dev/tty.Setareh-DevB";
	serial_port_base::baud_rate BAUD(38400);
	serial_port_base::character_size C_SIZE( 8 );

	serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
	serial_port_base::parity PARITY( serial_port_base::parity::even );
	serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );
	io_service io;
	port = new serial_port( io, PORT );
	port->set_option( BAUD );
	port->set_option( C_SIZE );
	port->set_option( PARITY );
}

Port::~Port(){
	fullStop();
	delete port;
}


bool Port::move(vector<geometry::Vector> path , MovingObj& agent){
	if(path.size()==0)
		return false;
	if( (agent.COM - path[path.size()-1]).size() < LIMITDEST ){//check the reverse path
		path.pop_back();
		if(path.size()==0)
			return false;
	}
	int angle =  path[path.size()-1].angle() - agent.COM.angle() - agent.direction;
	talkToSetare(SPEED , angle , 0);
	return true;
}

bool Port::safeMove(vector<geometry::Vector> path , MovingObj& agent){
	if(path.size()==0)
		return false;
	if( (agent.COM - path[path.size()-1]).size() < LIMITDEST ){//check the reverse path
		path.pop_back();
		if(path.size()==0)
			return false;
	}
	int rotation =  path[path.size()-1].angle() - agent.direction;
	talkToSetare(0 , 0 , rotation);
	talkToSetare(SPEED , 0 , 0);
	//check for talkToSetare(SPEED , 0 , rotation);
	return true;
}


void Port::fullStop(){
	writePort(115);
	writePort(0);
	writePort(0);
	writePort(0);
	writePort(0);
	writePort(170);
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

	writePort(115);
	writePort((int)abs(m1));
	writePort((int)abs(m2));
	writePort((int)abs(m3));
	writePort((int)abs(m4));
	writePort((int)abs(A));

	return;
}

void Port:: writePort(int input){
	unsigned char command[1] = {0};
	command[0] = static_cast<unsigned char>(input);
	write( *port, buffer( command, 1 ) );
	port->send_break();
	return;
}
