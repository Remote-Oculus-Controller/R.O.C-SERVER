#ifndef RTSP_FACTORY_HPP
#define RTSP_FACTORY_HPP

#include <iostream>
#include <vector>
#include <pthread.h>

#include <liveMedia.hh>
#include <GroupsockHelper.hh>
#include <BasicUsageEnvironment.hh>

#include "Network/H264LiveServerMediaSession.hpp"
#include "Encoder/x264Encoder.hpp"

typedef struct
{
	int cameraId;
	int port;
	char volatile * watcher;
} threadArguments;

class RTSPFactory
{
	public:

		RTSPFactory();
		~RTSPFactory();

		int createServer(int cameraId, int port);
		bool deleteServer(int serverId);
	
	private:

		static void * createRTSPServer(void * args);

		std::vector<char volatile *> watcher_pool;
	
};

#endif // RTSP_FACTORY_HPP
