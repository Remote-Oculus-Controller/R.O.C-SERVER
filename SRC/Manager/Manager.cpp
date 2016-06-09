#include "Manager/Manager.hpp"

Manager::Manager()
{
	logger::log(START_MANAGER , logger::INFO);
	this->_RTSPFactory = new RTSPFactory();
	logger::log(SUCCESS_MANAGER , logger::SUCCESS);
}

Manager::~Manager()
{
	delete this->_RTSPFactory;
	delete this->_videoHandler;
	delete this->_TcpServer;
	logger::log(STOP_MANAGER , logger::SUCCESS);
}

bool Manager::startRTSP()
{
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

bool Manager::startInterpretor()
{
	std::vector<std::string> tokens;
	sleep(1);

	while (1)
	{
		std::cout << ":> ";
		tokens = this->_reader.getTokens();
		if (tokens.size())
		{
			if (tokens[0] == "stop")
			{
				this->stopRTSP();
				this->stopInterpretor();
				break;
			}
			if (tokens[0] == "canny")
			{
				ImgProcessingWrapperSingleton::getInstance()->addProcessing(new CannyEdge() , 0);
			}
			if (tokens[0] == "clear")
			{
				ImgProcessingWrapperSingleton::getInstance()->clearProcessing();
			}
			if (tokens[0] == "face")
			{
				ImgProcessingWrapperSingleton::getInstance()->addProcessing(new FaceDetect() , 0);
			}
			if (tokens[0] == "zoom" && tokens[1] == "on")
			{
				this->_videoHandler->setAll(cv::CAP_PROP_ZOOM , std::stod(tokens[2].c_str()));
			}
			if (tokens[0] == "zoom" && tokens[1] == "off")
			{
				this->_videoHandler->setAll(cv::CAP_PROP_ZOOM , 0);
			}
			if (tokens[0] == "exposure")
			{
				this->_videoHandler->setAll(cv::CAP_PROP_EXPOSURE , std::stod(tokens[1].c_str()));
			}
		}
	}
	return true;
}

bool Manager::stopInterpretor()
{
	logger::log(STOP_INTERPRETOR , logger::logType::SUCCESS);
}

bool Manager::startVideoManager()
{
	this->_videoHandler = VideoManagerSingleton::getInstance();
	if (this->_videoHandler == NULL)
	return false;
	if (this->_videoHandler->isReady())
	{
		this->_videoHandler->run();
		logger::log(SUCCESS_VIDEOMANAGER , logger::logType::SUCCESS);
		return true;
	}
	return false;
}

bool Manager::stopVideoManager()
{
}

bool Manager::startTcpServer()
{
		std::thread * thread = new std::thread(&Manager::networkLoop , this);
		thread->detach();
		return true;
}

bool Manager::stopTcpServer()
{
	if (this->_TcpServer)
		delete this->_TcpServer;
}

void Manager::networkLoop()
{
	TcpPacket packet;
	size_t count;
	bool isProcessingOn = false;
	this->_TcpServer = new TcpServer(configuration::tcpPort);
	if (this->_TcpServer->initServer() == false || this->_TcpServer->runServer() == false)
		{
			logger::log("ERROR TCP" , logger::logType::FAILURE);
			return;
		}
	logger::log(SUCCESS_TCP, logger::logType::SUCCESS);
	while (1)
	{
		if ((count = this->_TcpServer->Read((char *)&packet , sizeof(packet))) <= 0)
			{
				logger::log("ERROR TCP" , logger::logType::FAILURE);
				return;
			}
		switch (packet.action)
		{
			case 0x0 :
				logger::log("STOP" , logger::logType::WARNING);
			break;
			case 0x1 :
				logger::log("ZOOM" , logger::logType::WARNING);
				this->_videoHandler->setAll(cv::CAP_PROP_ZOOM , packet.param1);
			break;
			case 0x2 :
				logger::log("GAIN" , logger::logType::WARNING);
				this->_videoHandler->setAll(cv::CAP_PROP_GAIN , packet.param1);
			break;
			case 0x3 :
				logger::log("HUE" , logger::logType::WARNING);
				this->_videoHandler->setAll(cv::CAP_PROP_HUE , packet.param1);
			break;
			case 0x4 :
				logger::log("BRIGHTNESS" , logger::logType::WARNING);
				this->_videoHandler->setAll(cv::CAP_PROP_BRIGHTNESS , packet.param1);
			break;
			case 0x5 :
				if (isProcessingOn)
					break;
				isProcessingOn = true;
				logger::log("CANNY ON" , logger::logType::WARNING);
				ImgProcessingWrapperSingleton::getInstance()->addProcessing(new CannyEdge(packet.param1 , packet.param2) , 0);
			break;
			case 0x6 :
				logger::log("CANNY OFF" , logger::logType::WARNING);
				ImgProcessingWrapperSingleton::getInstance()->clearProcessing();
				isProcessingOn = false;
			break;
			case 0x7 :
				if (isProcessingOn)
					break;
				isProcessingOn = true;
				logger::log("FACE ON" , logger::logType::WARNING);
				ImgProcessingWrapperSingleton::getInstance()->addProcessing(new FaceDetect(packet.param1) , 0);
			break;
			case 0x8 :
				logger::log("FACE OFF" , logger::logType::WARNING);
				ImgProcessingWrapperSingleton::getInstance()->clearProcessing();
				isProcessingOn = false;
			break;
			case 0x9 :
				logger::log("ID ON" , logger::logType::WARNING);
			break;
			case 0xA :
				logger::log("ID OFF" , logger::logType::WARNING);
				ImgProcessingWrapperSingleton::getInstance()->clearProcessing();
				isProcessingOn = false;
			break;
			case 0xB :
				logger::log("CLEAR" , logger::logType::WARNING);
				ImgProcessingWrapperSingleton::getInstance()->clearProcessing();
				isProcessingOn = false;
			break;
		}
	}
}
