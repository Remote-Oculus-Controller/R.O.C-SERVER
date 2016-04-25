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
    static LiveSourceWithx264* createNew(UsageEnvironment& env , unsigned int id);
    static EventTriggerId eventTriggerId;
protected:
    LiveSourceWithx264(UsageEnvironment& env , unsigned int id);
    virtual ~LiveSourceWithx264(void);
private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void* clientData);
    void deliverFrame();
    void encodeNewFrame();
    static unsigned referenceCount;
    std::queue<x264_nal_t> nalQueue;
    timeval currentTime;
    Camera * camera;
    x264Encoder *encoder;
    unsigned int _id;
};

#endif // LIVE_SOURCE_WITHX264_HPP
