#include "Manager/Manager.hpp"

Manager::Manager(int argc , char ** argv)
{
	this->_argc = argc;
	this->_argv = argv;
}

Manager::~Manager()
{

}

bool Manager::startRTSP()
{

	YAMLParser parser = YAMLParser(VIDEO_MANAGER_CONFIG_FILE , FileStorage::READ);
	if (parser.isOpened() == false)
		return false;

	unsigned int camerasCount = parser.getValueOf("camera_count");

	if (this->_argc < 2)
		return (false);

	int port = atoi(this->_argv[1]);

	if (port <= 0)
		return (false);

	if (this->_RTSPFactory.createServer(camerasCount, port) == -1)
		return (false);
	return (true);

}

bool Manager::stopRTSP()
{
	this->_RTSPFactory.deleteServer();
}

bool Manager::startInterpretor()
{
	std::vector<std::string> tokens;
	std::cout << "Waiting for RTSP Server..." << std::endl;
	sleep(1);

	while (1)
	{
		std::cout << ":> ";
		tokens = this->_reader.getTokens();
		if (tokens.size() && tokens[0] == "stop")
		{
			this->stopRTSP();
			break;
		}
	}
}

bool Manager::stopInterpretor()
{

}
