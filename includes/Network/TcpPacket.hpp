#ifndef TCP_PACKET_HPP
#define TCP_PACKET_HPP

#include <stdint.h>

#define MAGICNUMBER 0x4242

typedef struct _TcpPacket
{
	uint32_t	magicNumber;
	uint32_t	action;
	double  param1;
	double  param2;
}				TcpPacket;

// action 0x0 : stop
// action 0x1 : zoom  : param1 = value
// action 0x2 : gain  : param1 = value
// action 0x3 : hue   : param1 = value
// action 0x4 : bright: param1 = value
// action 0x5 : canny on : param1 = value param2 = value
// action 0x6 : canny off
// action 0x7 : face on: param1 = value
// action 0x8 : face off
// action 0x9 : ID on
// action 0xA : ID off
// action 0xB : clear processing

#endif // TCP_PACKET_HPP
