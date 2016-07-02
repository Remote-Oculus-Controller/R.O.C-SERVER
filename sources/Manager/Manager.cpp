#include "Manager/Manager.hpp"

Manager::Manager() {
    logger::log(START_MANAGER , logger::INFO);
    this->_videoManager = NULL;
    this->_networkManager = NULL;
		this->_RTSPManager = NULL;
		logger::log(SUCCESS_MANAGER , logger::SUCCESS);
}


Manager::Manager(const Manager & copy)
{
		this->_videoManager = copy._videoManager;
		this->_RTSPManager = copy._RTSPManager;
		this->_networkManager = copy._networkManager;
}

Manager::~Manager() {
    delete this->_RTSPManager;
    delete this->_videoManager;
    delete this->_networkManager;
    logger::log(STOP_MANAGER , logger::SUCCESS);
}

bool Manager::startRTSP() {

    this->_RTSPManager = new RTSPManager();
    if (this->_RTSPManager == NULL)
        return false;

    logger::log(START_RTSP , logger::INFO);

    for (unsigned int i = 0 ; i < configuration::camera_count ; i++) {
        if (this->_RTSPManager->createServer(i, configuration::port + i)) {
            return (false);
        }
    }

    logger::log(SUCCESS_RTSP , logger::logType::SUCCESS);
    return (true);
}

bool Manager::stopRTSP() {
    logger::log(STOP_RTSP , logger::logType::SUCCESS);
    this->_RTSPManager->deleteServer();
}

bool Manager::startVideoManager() {
    this->_videoManager = new VideoManager();
    if (this->_videoManager == NULL)
        return false;
    if (this->_videoManager->isReady()) {
        this->_videoManager->run();
        logger::log(SUCCESS_VIDEOMANAGER , logger::logType::SUCCESS);
        return true;
    }
    return false;
}

bool Manager::stopVideoManager() {
}

bool Manager::startNetworkManager() {
    this->_networkManager = new NetworkManager(this , configuration::tcpPort);
    if (this->_networkManager->init() == false)
        return false;
    this->_networkManager->run();
    return true;
}

bool Manager::stopNetworkManager() {

}

protocol::Packet * Manager::inputFlowPop() {
    std::unique_lock<std::mutex> _lock(_inputLock);
    protocol::Packet * elem = this->_inputFlow.front();
    this->_inputFlow.pop();
    return elem;
}

protocol::Packet * Manager::outputFlowPop() {
    std::unique_lock<std::mutex> _lock(_outputLock);
    protocol::Packet * elem = this->_outputFlow.front();
    this->_outputFlow.pop();
    return elem;
}

void Manager::inputFlowPush(protocol::Packet * toAdd) {
    std::unique_lock<std::mutex> _lock(_inputLock);
    this->_inputFlow.push(toAdd);
}

void Manager::outputFlowPush(protocol::Packet * toAdd) {
    std::unique_lock<std::mutex> _lock(_outputLock);
    this->_outputFlow.push(toAdd);
}

bool Manager::isInputFlowEmpty() {
    std::unique_lock<std::mutex> _lock(_inputLock);
    return this->_inputFlow.empty();
}

bool Manager::isOutputFlowEmpty() {
    std::unique_lock<std::mutex> _lock(_outputLock);
    return this->_outputFlow.empty();
}

void Manager::waitFlag() {
    while (Cleanup::flag == 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
