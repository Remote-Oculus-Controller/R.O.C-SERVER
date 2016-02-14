#ifndef TCP_PACKET_HPP
#define TCP_PACKET_HPP

#include <stdint.h>

#define MAGICNUMBER 0x4242



typedef struct _TcpPacket
{
	uint32_t	magicNumber;
	uint32_t	action;

}				TcpPacket;


#endif // TCP_PACKET_HPP
