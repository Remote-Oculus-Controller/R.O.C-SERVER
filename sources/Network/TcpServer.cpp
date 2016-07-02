#include <Network/TcpServer.hpp>


//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

TcpServer::TcpServer(unsigned short port) : Server(port) {
    this->_isSocketOpen = false;
    this->_isServerRunning = false;
}

TcpServer::~TcpServer() {
    if (this->_isSocketOpen == true)
        close(this->_socketClient);
    close(this->_socket);
}

//====================================================
// FONCTIONS SURCHARGEES d'INIT / MARCHE / ARRET
//====================================================

bool TcpServer::initServer() {
    int reuseaddr = 1;

    if (this->_isSocketOpen == true || this->_isServerRunning == true)
        return (false);

    if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (false);
    this->_isSocketOpen = true;

    CLEAR(&(this->_serverAdress));
    this->_serverAdress.sin_family 		= AF_INET;
    this->_serverAdress.sin_port 		= htons(this->_port);
    this->_serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
        perror("setsockopt");
        return 1;
    }

    if (bind(this->_socket, (struct sockaddr *) &(this->_serverAdress),
             this->_serverAdressLenght) < 0)
        return (false);

    if (listen(this->_socket, 1) < 0)
        return (false);
    logger::log(INFO_TCP_PORT(this->_port) , logger::logType::PRIORITY);
    return (true);
}

bool TcpServer::runServer() {
    if (this->_isSocketOpen == false || this->_isServerRunning == true)
        return false;
    logger::log(SUCCESS_TCP , logger::logType::SUCCESS);
    logger::log(INFO_TCP_CONNECTION , logger::logType::INFO);
    if ((this->_socketClient  = accept(this->_socket, (struct sockaddr *) NULL, NULL)) < 0) {
        logger::log(std::string("Error on accept : ") + std::string(strerror(errno)) , logger::logType::FAILURE);
        return false;
    }
    this->_isServerRunning = true;
    return true;
}

//====================================================
// FONCTIONS SURCHARGEES D'ENVOI ET DE RECEPTION
//====================================================

size_t TcpServer::Read(char *buffer, size_t bufferLenght) {
    if (this->_isServerRunning == false)
        return (-1);
    return (recv(this->_socketClient, buffer, bufferLenght, 0));
}

size_t TcpServer::Send(char *buffer, size_t bufferLenght) {
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