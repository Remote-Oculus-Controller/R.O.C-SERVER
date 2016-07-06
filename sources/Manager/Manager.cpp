#include "Manager/Manager.hpp"

Manager::Manager()
{
	logger::log(START_MANAGER , logger::INFO);
	this->_videoManager = NULL;
	this->_RTSPFactory = NULL;
	this->_networkManager = NULL;
	this->_networkInterpretor = NULL;
	logger::log(SUCCESS_MANAGER , logger::SUCCESS);
}

Manager::~Manager()
{
	delete this->_RTSPFactory;
	delete this->_videoManager;
	delete this->_networkManager;
	logger::log(STOP_MANAGER , logger::SUCCESS);
}

bool Manager::startRTSP()
{

	this->_RTSPFactory = new RTSPFactory();
	if (this->_RTSPFactory == NULL)
		return false;

	logger::log(START_RTSP , logger::INFO);

	for (unsigned int i = 0 ; i < configuration::camera_count ; i++)
	{
		if (this->_RTSPFactory->createServer(i, configuration::port + i)) {
			return (false);
		}
	}

	logger::log(SUCCESS_RTSP , logger::logType::SUCCESS);
	return (true);
}

bool Manager::stopRTSP()
{
	logger::log(STOP_RTSP , logger::logType::SUCCESS);
	this->_RTSPFactory->deleteServer();
}

bool Manager::startVideoManager()
{
	this->_videoManager = VideoManagerSingleton::getInstance();
	if (this->_videoManager == NULL)
	return false;
	if (this->_videoManager->isReady())
	{
		this->_videoManager->run();
		logger::log(SUCCESS_VIDEOMANAGER , logger::logType::SUCCESS);
		return true;
	}
	return false;
}

bool Manager::stopVideoManager()
{
}

bool Manager::startNetworkManager()
{
	this->_networkManager = new NetworkManager(this , configuration::tcpPort);
	if (this->_networkManager->init() == false)
		return false;
	this->_networkManager->run();
	return true;
}

bool Manager::stopNetworkManager()
{

}

bool Manager::startNetworkInterpretor()
{
	this->_networkInterpretor = new NetworkInterpretor(this);
	if (this->_networkInterpretor == NULL)
		return false;
	this->_networkInterpretor->run();
	return true;
}

bool Manager::stopNetworkInterpretor()
{

}

void Manager::waitFlag()
{
	while (Cleanup::flag == 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


bool Manager::isInputAvailable()
{
	std::unique_lock<std::mutex> _lock(_inputLock);
	return !this->_input.empty();
}

bool Manager::isOutputAvailable()
{
	std::unique_lock<std::mutex> _lock(_outputLock);
 	return !this->_output.empty();
 }

void Manager::pushInput(protocol::Packet * elem)
{
	std::unique_lock<std::mutex> _lock(_inputLock);
	this->_input.push(elem);

}

void Manager::pushOutput(protocol::Packet * elem)
{
	std::unique_lock<std::mutex> _lock(_outputLock);
	this->_output.push(elem);
}

protocol::Packet * Manager::popInput()
{
	protocol::Packet * elem;
	std::unique_lock<std::mutex> _lock(_inputLock);
	elem =  this->_input.back();
	this->_input.pop();
	return elem;
}

protocol::Packet * Manager::popOutput()
{
	protocol::Packet * elem;
	std::unique_lock<std::mutex> _lock(_outputLock);
	elem =  this->_output.back();
	this->_output.pop();
	return elem;
}
