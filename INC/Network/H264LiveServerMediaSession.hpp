#ifndef H264LIVE_SERVER_MEDIA_SESSION_HPP
#define H264LIVE_SERVER_MEDIA_SESSION_HPP

#include "liveMedia.hh"
#include "OnDemandServerMediaSubsession.hh"
#include "LiveSourceWithx264.hpp"

class H264LiveServerMediaSession :public OnDemandServerMediaSubsession
{
public:
    static H264LiveServerMediaSession* createNew(UsageEnvironment& env, bool reuseFirstSource, unsigned int id);
    void checkForAuxSDPLine1();
    void afterPlayingDummy1();
protected:
    H264LiveServerMediaSession(UsageEnvironment& env, bool reuseFirstSource, unsigned int id);
    virtual ~H264LiveServerMediaSession(void);
    void setDoneFlag() { fDoneFlag = ~0; }
protected:
    virtual char const* getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource);
    virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
private:
    char* fAuxSDPLine;
    char fDoneFlag;
    RTPSink* fDummySink;
    unsigned int _id;
};

#endif // H264LIVE_SERVER_MEDIA_SESSION_HPP
