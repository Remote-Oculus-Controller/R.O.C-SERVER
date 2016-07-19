#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define CLEAR(param) memset(param, 0, sizeof(*param))


	// CLASSE ABSTRAITE DE BASE QUI PERMET L'INSTANCIATION DES CLASSES
	// UdpServer et  TcpServer

class Server
{

	public:

	//====================================================
	// CONSTRUCTEUR / DESTRUCTEUR
	//====================================================

	Server(unsigned short port);
	virtual ~Server();

	//====================================================
	// FONCTIONS VIRTUELLES PURES
	//
	// initServer : Initialise le serveur suivant les par-
	//				amètres donnés
	//
	// runServer  : Démarre le serveur
	//
	// stopServer : Arette le serveur
	//
	// read       : Lit la socket
	//
	// send		  : Ecrit sur la socket
	//====================================================

	virtual bool initServer() = 0;
	virtual bool runServer() = 0;
	virtual bool stopServer();

	virtual int Read(char *buffer, size_t bufferLenght) = 0;
	virtual size_t Send(char *buffer, size_t bufferLenght) = 0;

	//====================================================
	// GETTERS DES PARAMETRES BASIQUES DU SERVEUR
	//====================================================

	virtual char getPort();
	virtual bool getIsServerRunning();
	virtual bool getIsSocketOpen();
	virtual long unsigned  getClientIp();

	//====================================================
	// Fonction Statique de conversion de String en short
	//====================================================

	static unsigned short getShortFromString(char *port);

	protected:

	//====================================================
	// ATTRIBUTS BASIQUES DU SERVEUR
	//====================================================

	unsigned short		_port;
	int 							_socket;
	struct sockaddr_in 	_serverAdress;
	socklen_t						_serverAdressLenght;

	bool 				_isSocketOpen;
	bool 				_isServerRunning;



};

#endif // SERVER_HPP
