#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "RTSPFactory/RTSPFactory.hpp"
#include "Interpretor/Reader.hpp"
#include "Singletons/VideoManagerSingleton.hpp"
#include "Singletons/ImgProcessingWrapperSingleton.hpp"
#include "Processing/CannyEdge.hpp"
#include "Processing/FaceDetect.hpp"
#include "Logger/Logger.hpp"
#include "Parser/ConfigParser.hpp"
#include "Network/TcpServer.hpp"

class Manager
{
	public:

	Manager();
	~Manager();

	bool startRTSP();
	bool stopRTSP();

	bool startVideoManager();
	bool stopVideoManager();

	bool startInterpretor();
	bool stopInterpretor();

	bool startTcpServer();
	bool stopTcpServer();

	private:

	void networkLoop();

	Reader 					_reader;
	RTSPFactory  *	_RTSPFactory;
	VideoManager * 	_videoHandler;
	TcpServer * 		_TcpServer;

	// TCP Server 	(get and send commands)
	// Interpretor
	// Controls
};

#endif // MANAGER_HPP
