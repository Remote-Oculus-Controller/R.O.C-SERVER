#include <Network/TcpServer.hpp>

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

TcpServer::TcpServer(unsigned short port) : Server(port)
{
	this->_isSocketOpen = false;
	this->_isServerRunning = false;
}

TcpServer::~TcpServer()
{
	if (this->_isSocketOpen == true)
		close(this->_socketClient);
	close(this->_socket);
}

//====================================================
// FONCTIONS SURCHARGEES d'INIT / MARCHE / ARRET
//====================================================

bool TcpServer::initServer()
{
	if (this->_isSocketOpen == true || this->_isServerRunning == true)
		return (false);

	if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (false);
	this->_isSocketOpen = true;

	CLEAR(&(this->_serverAdress));
	this->_serverAdress.sin_family 		= AF_INET;
	this->_serverAdress.sin_port 		= htons(this->_port);
	this->_serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->_socket, (struct sockaddr *) &(this->_serverAdress),
		 this->_serverAdressLenght) < 0)
		return (false);

	if (listen(this->_socket, 1) < 0)
		return (false);
	logger::log(INFO_TCP_PORT(this->_port) , logger::logType::PRIORITY);
	return (true);
}

bool TcpServer::runServer()
{
	if (this->_isSocketOpen == false || this->_isServerRunning == true)
		return false;
	logger::log("Waiting TCP connection..." , logger::logType::INFO);
	if ((this->_socketClient  = accept(this->_socket, (struct sockaddr *) NULL, NULL)) < 0) {
		logger::log("Error on accept !" , logger::logType::FAILURE);
		return false;
	}
	this->_isServerRunning = true;
	return true;
}

//====================================================
// FONCTIONS SURCHARGEES D'ENVOI ET DE RECEPTION
//====================================================

size_t TcpServer::Read(char *buffer, size_t bufferLenght)
{
	if (this->_isServerRunning == false)
        return (-1);

	struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 0;
    tv.tv_usec = 5000;

    FD_ZERO(&readfds);
    FD_SET(_socketClient, &readfds);

    if (select(_socketClient+1, &readfds, NULL, NULL, &tv) <= 0)
        return 0;

    if (FD_ISSET(_socketClient, &readfds))
        return (recv(this->_socketClient, buffer, bufferLenght, 0));
    else
        return 0;
}

size_t TcpServer::Send(char *buffer, size_t bufferLenght)
{
	if (this->_isServerRunning == false)
		return (-1);
	return (send(this->_socketClient, buffer, bufferLenght, 0));
}

bool TcpServer::discardClient() {
    if (this->_isSocketOpen == false)
        return false;
    close(this->_socketClient);
    this->_isServerRunning = false;
    return true;
}
