#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp> 
#include"../Include/Controller.h"
using namespace::boost::asio;
using std::cin;

const char *PORT = "/dev/tty.Setareh-DevB";

serial_port_base::baud_rate BAUD(38400);
serial_port_base::character_size C_SIZE( 8 );
serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
serial_port_base::parity PARITY( serial_port_base::parity::even );
serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );

void talkToSetare(int velocity, int angle, int rotation)
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
    {
        A|=1<<0;
    }
    else if(m1<0)
    {
        A|=1<<1;
    }

    if(m2>0)
    {
        A|=1<<2;
    }
    else if(m2<0)
    {
        A|=1<<3;
    }

    if(m3>0)
    {
        A|=1<<4;
    }
    else if(m3<0)
    {
        A|=1<<5;
    }

    if(m4>0)
    {
        A|=1<<6;
    }
    else if(m4<0)
    {
        A|=1<<7;
    }

        
    io_service io;
	  serial_port port( io, PORT );

	  port.set_option( BAUD );
	  port.set_option( C_SIZE );
	  port.set_option( PARITY );

    unsigned char command[1] = {0};
    unsigned char cmdInt[] = {115,abs(m1),abs(m2),abs(m3),abs(m4),A}; 
    cout<<(int)A<<endl;

	  for (int i =0; i < 6; i++) {
		  command[0] = static_cast<unsigned char>(cmdInt[i]);
		  write( port, buffer( command, 1 ) );
	  }
    port.send_break();
}


