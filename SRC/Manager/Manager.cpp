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
