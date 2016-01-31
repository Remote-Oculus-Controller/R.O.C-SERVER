#include "RTSPFactory/RTSPFactory.hpp"

RTSPFactory::RTSPFactory()
{

}

RTSPFactory::~RTSPFactory()
{
	for (unsigned int i = 0 ; i < this->watcher_pool.size() ; i++)
	{
		*(this->watcher_pool[i]) = 1;
	}
}


int RTSPFactory::createServer(int cameraId, int port)
{
	static int serverID = 0;

	threadArguments * args = new threadArguments;

	args->cameraId = cameraId;
	args->port = port;
	args->watcher = 0; 

	watcher_pool.push_back(&(args->watcher));

	pthread_t thread;

	if (pthread_create(&thread, NULL,  &RTSPFactory::createRTSPServer , args) == -1)
		{
			watcher_pool.pop_back();
			return (-1);
		}

	serverID += 1;
	return (serverID - 1);
}

bool RTSPFactory::deleteServer(int serverId)
{
	*(this->watcher_pool[serverId]) = 1;
	this->watcher_pool.erase(this->watcher_pool.begin() + serverId);
	return (true);
}

void * RTSPFactory::createRTSPServer(void * args_void)
{
	threadArguments * args = static_cast<threadArguments *>(args_void);

	TaskScheduler* taskSchedular = BasicTaskScheduler::createNew();
    BasicUsageEnvironment* usageEnvironment = BasicUsageEnvironment::createNew(*taskSchedular);
    RTSPServer* rtspServer = RTSPServer::createNew(*usageEnvironment, args->port, NULL);
    
    if(rtspServer == NULL)
    {
        *usageEnvironment << "Failed to create rtsp server ::" << usageEnvironment->getResultMsg() <<"\n";
        exit(1);
    }

    std::string streamName = "camera_" + std::to_string(args->cameraId);
    ServerMediaSession* sms = ServerMediaSession::createNew(*usageEnvironment, streamName.c_str(), streamName.c_str(), "Live H264 Stream");
    H264LiveServerMediaSession *liveSubSession = H264LiveServerMediaSession::createNew(*usageEnvironment, true);
    sms->addSubsession(liveSubSession);
    rtspServer->addServerMediaSession(sms);
    char* url = rtspServer->rtspURL(sms);
    *usageEnvironment << "Play the stream using url "<<url << "\n";
    delete[] url;
    taskSchedular->doEventLoop(&args->watcher);
    return 0;
}