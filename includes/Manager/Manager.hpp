#ifndef  MANAGER_HPP
#define 	MANAGER_HPP

#include "RTSPManager/RTSPManager.hpp"
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

class Manager {
  public:

    Manager();
    ~Manager();

    bool startRTSP();
    bool stopRTSP();

    bool startVideoManager();
    bool stopVideoManager();

    bool startNetworkManager();
    bool stopNetworkManager();

    bool isInputFlowEmpty();
    bool isOutputFlowEmpty();

    protocol::Packet * inputFlowPop();
    protocol::Packet * outputFlowPop();

    void inputFlowPush(protocol::Packet * toAdd);
    void outputFlowPush(protocol::Packet * toAdd);

    void waitFlag();

  private:

    RTSPManager  *		_RTSPManager;
    VideoManager * 		_videoManager;
    NetworkManager * 	_networkManager;

    std::queue<protocol::Packet *> _inputFlow;
    std::queue<protocol::Packet *> _outputFlow;

    std::mutex 	_inputLock;
    std::mutex 	_outputLock;

};

#endif // MANAGER_HPP
