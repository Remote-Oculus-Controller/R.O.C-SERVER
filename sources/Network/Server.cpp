#include "Network/Server.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

Server::Server(unsigned short port)
{
	this->_isSocketOpen = false;
	this->_isServerRunning = false;
	this->_port = port;
	this->_serverAdressLenght = sizeof(this->_serverAdress);
}

Server::~Server()
{
	if (this->_isSocketOpen == true)
	{
		if (this->_isServerRunning == true)
			this->stopServer();
		if (close(this->_isSocketOpen) == -1)
			std::cout << "Error while closing socket..." << std::endl;
	}
}

//====================================================
// GETTERS DES PARAMETRES BASIQUES DU SERVEUR
//====================================================

char Server::getPort()
{
	return (this->_port);
}

bool Server::getIsServerRunning()
{
	return (this->_isServerRunning);
}

bool Server::getIsSocketOpen()
{
	return (this->_isSocketOpen);
}

unsigned long Server::getClientIp()
{
	return (this->_serverAdress.sin_addr.s_addr);
}

//====================================================
// Fonction d'arret
//====================================================

bool Server::stopServer()
{
  if (this->_isServerRunning == false)
    return (false);
  this->_isServerRunning = false;
  return (true);
}
//====================================================
// Fonction Statique de conversion de String en short
//====================================================

unsigned short Server::getShortFromString(char *port)
{
	std::stringstream stream;
	short convertedPort;

	stream << port;
	stream >> convertedPort;

	return (convertedPort);
}
