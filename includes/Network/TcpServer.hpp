#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "Network/Server.hpp"
#include "Network/TcpPacket.hpp"
#include "Logger/Logger.hpp"

class TcpServer : public Server
{
	public:

	//====================================================
	// CONSTRUCTEUR / DESTRUCTEUR
	//====================================================

	TcpServer(unsigned short port);
	virtual ~TcpServer();

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

	protected:

	//====================================================
	// ATTRIBUT PROPRE AU SERVEUR TCP
	//====================================================

	int 	_socketClient;
};

#endif // TCP_SERVER_HPP
