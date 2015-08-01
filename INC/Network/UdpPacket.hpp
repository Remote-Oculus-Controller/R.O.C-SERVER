#ifndef UDP_PACKET_HPP
#define UDP_PACKET_HPP

#include <stdint.h>

//============================================
// TAILLE COMPLETE D'UN PAQUET UDP
//
//	-> 512
//  -> 1024
//  -> 2048
//  -> 4096
//
//============================================

#define DATA_LENGHT 512

//============================================
// HEADER D'UN PAQUET UDP
//
// frameID : ID de la frame généré en random
//
// packetID: définit la position du paquet
//
// packetSize : taille du buffer data
//============================================

typedef struct _UdpHeader
{
	uint32_t	packetSize;
	uint32_t 	resetID;
	uint16_t	frameID;
	uint16_t	packetID;
	uint32_t 	maxPacketID;
}				UdpHeader;

//===========================================
// PAQUET UDP
//
// header : Header définit plus haut
//
// data   : les données a envoyer
//===========================================

typedef struct _UdpPacket
{
	UdpHeader 	header;
	uint8_t		data[DATA_LENGHT- sizeof(UdpHeader)];
}				UdpPacket;

#endif // UDP_PACKET_HPP
