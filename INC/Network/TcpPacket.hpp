#ifndef TCP_PACKET_HPP
#define TCP_PACKET_HPP

#include <stdint.h>

#define MAGICNUMBER 0x4242

//============================================
// PAQUET TCP
//
// action : action a effectuer
//
// lastFPS: dernière moyenne de FPS utilisé
//			pour la synchronisation
//
// lastMS : dernière moyenne du temp de laten-
//			ce utilisé pour la synchronisation
//============================================

typedef struct _TcpPacket
{
	uint16_t	magicNumber;
	uint16_t	lastMS;
	uint8_t		action;
	uint8_t		lastFPS;
}				TcpPacket;


#endif // TCP_PACKET_HPP
