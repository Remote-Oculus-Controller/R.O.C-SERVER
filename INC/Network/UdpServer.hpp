#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <thread>
#include <vector>
#include "Network/Server.hpp"
#include "Network/UdpPacket.hpp"

class UdpServer : public Server
{
	public:
	
	//====================================================
	// CONSTRUCTEUR / DESTRUCTEUR
	//====================================================

	UdpServer(unsigned short port, unsigned long ip = INADDR_ANY);
	virtual ~UdpServer();

	//====================================================
	// FONCTIONS SURCHARGEES d'INIT / MARCHE 
	//====================================================

	virtual bool initServer();
	virtual bool runServer();

	//====================================================
	// FONCTIONS SURCHARGEES D'ENVOI ET DE RECEPTION
	//====================================================
	
	virtual size_t Read(char *buffer, size_t bufferLenght);
	virtual size_t Send(char *buffer, size_t bufferLenght);

  	//====================================================
	// FONCTION PUBLIQUE DE CREATION DE PACKET
	//====================================================

	void bundleUpData(std::vector<unsigned char> *data, int threadCount = 1);
         std::vector<UdpPacket> * getBundledUpData();


	protected:

	//====================================================
	// FONCTION STATIQUE DE CREATION DE PACKET
	//====================================================
	
	static UdpPacket * getNewPacket();

	//====================================================
	// FONCTION PROTECTED DE CREATION DE PACKET
	//====================================================

	void fillPacketArray(UdpHeader header, std::vector<unsigned char> * data, int packetCount);
	

	//====================================================
	// ATTRIBUT PROPRE AU SERVEUR UDP
	//====================================================

	struct sockaddr_in _clientAdress;
	socklen_t		   _clientAdressLenght;
	unsigned long	   _clientIp;
  
       std::vector<UdpPacket> * bundledUpData;

};

#endif // UDP_SERVER_HPP
