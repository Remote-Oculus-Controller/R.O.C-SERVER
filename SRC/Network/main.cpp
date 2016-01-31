#include <iostream>
#include <liveMedia.hh>
#include "BasicUsageEnvironment.hh"
#include <GroupsockHelper.hh>
#include "H264LiveServerMediaSession.hpp"
#include "opencv2/opencv.hpp"
#include "x264Encoder.hpp" 

int main(int argc, char* argv[])
{
    TaskScheduler* taskSchedular = BasicTaskScheduler::createNew();
    BasicUsageEnvironment* usageEnvironment = BasicUsageEnvironment::createNew(*taskSchedular);
    RTSPServer* rtspServer = RTSPServer::createNew(*usageEnvironment, 8555, NULL);
    if(rtspServer == NULL)
    {
        *usageEnvironment << "Failed to create rtsp server ::" << usageEnvironment->getResultMsg() <<"\n";
        exit(1);
    }

    std::string streamName = "usb1";
    ServerMediaSession* sms = ServerMediaSession::createNew(*usageEnvironment, streamName.c_str(), streamName.c_str(), "Live H264 Stream");
    H264LiveServerMediaSession *liveSubSession = H264LiveServerMediaSession::createNew(*usageEnvironment, true);
    sms->addSubsession(liveSubSession);
    rtspServer->addServerMediaSession(sms);
    char* url = rtspServer->rtspURL(sms);
    *usageEnvironment << "Play the stream using url "<<url << "\n";
    delete[] url;
    taskSchedular->doEventLoop();
    return 0;
}