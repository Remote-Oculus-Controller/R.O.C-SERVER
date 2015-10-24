#include "Network/UdpServer.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

UdpServer::UdpServer(unsigned short port, unsigned long ip) : Server(port)
{
	this->_clientIp = ip;
	this->_clientAdressLenght = sizeof(this->_clientAdress);
	bundledUpData = new std::vector<UdpPacket>;
}

UdpServer::~UdpServer()
{
	delete (bundledUpData);
}

//====================================================
// FONCTIONS SURCHARGEES d'INIT / MARCHE / ARRET 
//====================================================

bool UdpServer::initServer()
{
	if (this->_isSocketOpen == true || this->_isServerRunning == true)
		return (false);
	if ((this->_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return (false);
	this->_isSocketOpen = true;

	CLEAR(&(this->_serverAdress));
	this->_serverAdress.sin_family 		= AF_INET;
	this->_serverAdress.sin_port 		= htons(this->_port);
	this->_serverAdress.sin_addr.s_addr = this->_clientIp;

	if (bind(this->_socket, (struct sockaddr *) &(this->_serverAdress),
		 this->_serverAdressLenght) < 0)
		return (false);
	return (true);
}

bool UdpServer::runServer()
{
	if (this->_isSocketOpen == false || this->_isServerRunning == true)
		return (false);
	this->_isServerRunning = true;
}


//====================================================
// FONCTIONS SURCHARGEES D'ENVOI ET DE RECEPTION
//====================================================

size_t UdpServer::Read(char *buffer, size_t bufferLenght)
{
	if (this->_isServerRunning == false)
		return (-1);
	return(recvfrom(this->_socket, buffer, bufferLenght, 0,
	 (struct sockaddr *) &(this->_clientAdress), &(this->_clientAdressLenght)));
}

size_t UdpServer::Send(char *buffer, size_t bufferLenght)
{
	if (this->_isServerRunning == false)
		return (-1);
	return(sendto(this->_socket, buffer, bufferLenght, 0,
	 (struct sockaddr *) &(this->_clientAdress), this->_clientAdressLenght));
}

//====================================================
// FONCTION STATIQUE DE CREATION DE PACKET
//====================================================

UdpPacket * UdpServer::getNewPacket()
{
	UdpPacket * newPacket = new UdpPacket;
	if (newPacket)
		CLEAR(newPacket);
	return (newPacket);
}

std::vector<UdpPacket> * UdpServer::getBundledUpData()
{
  return (this->bundledUpData);
}

//====================================================
// FONCTION PROTECTED DE CREATION DE PACKET
//====================================================
#include <iostream>

void UdpServer::fillPacketArray(UdpHeader header, std::vector<unsigned char> * data, int packetCount)
{
	UdpPacket packet;
	int position;
	int toCopy;

	for (int i = 0; i < packetCount; i++)
	{
	        position = header.packetID * (DATA_LENGHT - sizeof(UdpHeader));
		if ((data->size() - position) < (DATA_LENGHT - sizeof(UdpHeader)))
		  toCopy = data->size() - position;
		else
		  toCopy   = (DATA_LENGHT - sizeof(UdpHeader)) % (data->size() - position);

		header.packetSize = toCopy;
		packet.header = header;
		memcpy(packet.data, &((*data)[position]), toCopy);
		(*bundledUpData)[header.packetID] = packet;		
		header.packetID++;
	}
}

//====================================================
// FONCTION PUBLIQUE DE CREATION DE PACKET
//====================================================

void UdpServer::bundleUpData(std::vector<unsigned char> * data, int threadCount)
{
	static uint32_t frameID = 0;
	size_t vectorSize;
	UdpHeader header;
	std::vector<std::thread> threads;
	int packetCount;
	int lastPacketCount;

	frameID = frameID + 1;
	if (frameID == 10000000)
		{
			header.resetID = 1;
			frameID = 0;
		}

	header.frameID = frameID;
	header.packetID = 0;
	vectorSize  = data->size() / (DATA_LENGHT - sizeof(UdpHeader));
	if (data->size() % (DATA_LENGHT - sizeof(UdpHeader)))
	  vectorSize++;
	this->bundledUpData->resize(vectorSize);
	header.maxPacketID = vectorSize - 1;
	header.packetID = packetCount;
	packetCount = vectorSize / threadCount;
	lastPacketCount = packetCount + (vectorSize % threadCount);

	for (int i = 1; i < threadCount ; i++)
	{
	  header.packetID += packetCount;
	  if (i + 1 == threadCount)
	    threads.push_back(std::thread(&UdpServer::fillPacketArray, this, header, data, lastPacketCount));
	  else
	    threads.push_back(std::thread(&UdpServer::fillPacketArray, this, header, data, packetCount)); 
	}

	header.packetID = 0;
	if (threadCount == 1)
	  this->fillPacketArray(header, data, lastPacketCount);
	else
	  this->fillPacketArray(header, data, packetCount);
	for (auto& th : threads) th.join();

}
