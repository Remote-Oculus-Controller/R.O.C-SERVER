#ifndef LIVE_SOURCE_WITHX264_HPP
#define LIVE_SOURCE_WITHX264_HPP

#include <queue>
#include "FramedSource.hh"
#include "Encoder/x264Encoder.hpp"


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

#include "Video/Camera.hpp"

class LiveSourceWithx264 : public FramedSource
{
public:
    static LiveSourceWithx264* createNew(UsageEnvironment& env);
    static EventTriggerId eventTriggerId;
protected:
    LiveSourceWithx264(UsageEnvironment& env);
    virtual ~LiveSourceWithx264(void);
private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
    void deliverFrame();
    void encodeNewFrame();
    static unsigned referenceCount;
    std::queue<x264_nal_t> nalQueue;
    timeval currentTime;
    // videoCaptureDevice is my BGR data source. You can have according to your need

    Camera * camera;
    // Remember the x264 encoder wrapper we wrote in the start
    x264Encoder *encoder;
}; 

#endif // LIVE_SOURCE_WITHX264_HPP
