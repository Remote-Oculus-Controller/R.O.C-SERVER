#ifndef RTSP_FACTORY_HPP
#define RTSP_FACTORY_HPP

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <liveMedia.hh>
#include <GroupsockHelper.hh>
#include <BasicUsageEnvironment.hh>

#include "Network/H264LiveServerMediaSession.hpp"
#include "Encoder/x264Encoder.hpp"
#include "Logger/Logger.hpp"


class RTSPFactory
{
	public:

		RTSPFactory();
		~RTSPFactory();

		int createServer(int cameraId, int port);
		bool deleteServer();

	private:

		void createRTSPServer(unsigned int id , unsigned int port , volatile char * watcher);
		char volatile * watcher;
		bool volatile _done;
		std::mutex _lock;
		std::condition_variable _condition;
};

#endif // RTSP_FACTORY_HPP
