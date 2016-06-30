#include "RTSPFactory/RTSPFactory.hpp"

RTSPFactory::RTSPFactory()
{
	this->watcher = new char;
	*(this->watcher) = 0;
	OutPacketBuffer::maxSize = 131072;
}


RTSPFactory::~RTSPFactory()
{
	this->deleteServer();
}


int RTSPFactory::createServer(int id, int port)
{	
	std::unique_lock<std::mutex> lock(_lock);
	this->_done = false;

	std::thread * thread = new std::thread(&RTSPFactory::createRTSPServer , this , id , port , this->watcher);
	thread->detach();

	while (this->_done == false)
		this->_condition.wait(lock);

	if (*(this->watcher) != 0) {
		return 1;
	}
	return 0;
}

bool RTSPFactory::deleteServer()
{
	if (this->watcher)
	{
		*(this->watcher) = 1;
		return (true);
	}
	else
		return (false);
}

void  RTSPFactory::createRTSPServer(unsigned int id , unsigned int port , volatile char * watcher)
{
	std::unique_lock<std::mutex> lock(_lock);
	TaskScheduler* taskSchedular = BasicTaskScheduler::createNew();
	BasicUsageEnvironment* usageEnvironment = BasicUsageEnvironment::createNew(*taskSchedular);
	RTSPServer* rtspServer = RTSPServer::createNew(*usageEnvironment, port, NULL);

	if(rtspServer == NULL)
	{
		logger::log(usageEnvironment->getResultMsg() , logger::logType::FAILURE);
		*watcher = -1;
		this->_done = true;
		this->_condition.notify_all();
		return;
	}

		H264LiveServerMediaSession *liveSubSession = H264LiveServerMediaSession::createNew(*usageEnvironment, true , id);
		std::string streamName = "camera_" + std::to_string(id);
		ServerMediaSession* sms = ServerMediaSession::createNew(*usageEnvironment, streamName.c_str(), streamName.c_str(), "Live H264 Stream");
		sms->addSubsession(liveSubSession);
		rtspServer->addServerMediaSession(sms);
		char* url = rtspServer->rtspURL(sms);
		logger::log(INFO_RTSP_URL(url) , logger::logType::PRIORITY);
		delete[] url;

		this->_done = true;
		this->_condition.notify_all();
		lock.unlock();
		taskSchedular->doEventLoop(watcher);

		return;
}
