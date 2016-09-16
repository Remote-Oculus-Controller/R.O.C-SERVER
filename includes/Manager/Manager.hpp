#ifndef  MANAGER_HPP
#define 	MANAGER_HPP

#include <queue>

#include "RTSPFactory/RTSPFactory.hpp"
#include "Interpretor/Reader.hpp"
#include "Interpretor/NetworkInterpretor.hpp"
#include "Singletons/VideoManagerSingleton.hpp"
#include "Singletons/ImgProcessingWrapperSingleton.hpp"
#include "Processing/CannyEdge.hpp"
#include "Processing/FaceDetect.hpp"
#include "Logger/Logger.hpp"
#include "Parser/ConfigParser.hpp"
#include "Network/NetworkManager.hpp"
#include "Manager/Cleanup.hpp"
#include "proto.pb.h"

class NetworkManager;
class NetworkInterpretor;

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

	bool startNetworkInterpretor();
	bool stopNetworkInterpretor();

	VideoManager * getVideoManager();
	NetworkManager * getNetworkManager();
	NetworkInterpretor * getNetworkInterpretor();
	RTSPFactory * getRTSPFactory();

	void waitFlag();

	bool isInputAvailable();
	bool isOutputAvailable();

	void pushInput(rocproto::Packet *);
	void pushOutput(rocproto::Packet *);

	rocproto::Packet * popInput();
	rocproto::Packet * popOutput();



	private:

	std::queue<rocproto::Packet *> _input;
	std::queue<rocproto::Packet *> _output;

	std::mutex _inputLock;
	std::mutex _outputLock;

	RTSPFactory  *				_RTSPFactory;
	VideoManager * 				_videoManager;
	NetworkManager * 			_networkManager;
	NetworkInterpretor * 	_networkInterpretor;
};

#endif // MANAGER_HPP
