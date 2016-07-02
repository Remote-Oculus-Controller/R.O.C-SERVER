#ifndef  MANAGER_HPP
#define 	MANAGER_HPP

#include <queue>

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
#include "proto.pb.h"

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

	bool isInputAvailable();
	bool isOutputAvailable();

	void pushInput(protocol::Packet *);
	void pushOutput(protocol::Packet *);

	protocol::Packet * popInput();
	protocol::Packet * popOutput();

	private:

	std::queue<protocol::Packet *> _input;
	std::queue<protocol::Packet *> _output;

	std::mutex _inputLock;
	std::mutex _outputLock;

	Reader 						_reader;
	RTSPFactory  *		_RTSPFactory;
	VideoManager * 		_videoManager;
	NetworkManager * 	_networkManager;

};

#endif // MANAGER_HPP
