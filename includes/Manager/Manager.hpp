#ifndef  MANAGER_HPP
#define 	MANAGER_HPP

#include "RTSPFactory/RTSPFactory.hpp"
#include "Interpretor/Reader.hpp"
#include "Singletons/VideoManagerSingleton.hpp"
#include "Singletons/ImgProcessingWrapperSingleton.hpp"
#include "Processing/CannyEdge.hpp"
#include "Processing/FaceDetect.hpp"
#include "Logger/Logger.hpp"
#include "Parser/ConfigParser.hpp"
#include "Network/NetworkManager.hpp"
#include "Manager/Cleanup.hpp"

class NetworkManager;

class Manager
{
	public:

	Manager();
	~Manager();

	bool startRTSP();
	bool stopRTSP();

	bool startVideoManager();
	bool stopVideoManager();

	bool startNetworkManager();
	bool stopNetworkManager();

	void waitFlag();

	private:

	Reader 						_reader;
	RTSPFactory  *		_RTSPFactory;
	VideoManager * 		_videoManager;
	NetworkManager * 	_networkManager;

};

#endif // MANAGER_HPP
