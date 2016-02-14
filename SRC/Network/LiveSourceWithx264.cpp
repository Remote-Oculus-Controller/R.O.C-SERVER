#include "Network/LiveSourceWithx264.hpp"
#include "Video/Camera.hpp"

LiveSourceWithx264* LiveSourceWithx264::createNew(UsageEnvironment& env)
{
    return new LiveSourceWithx264(env);
}

EventTriggerId LiveSourceWithx264::eventTriggerId = 0;

unsigned LiveSourceWithx264::referenceCount = 0;

LiveSourceWithx264::LiveSourceWithx264(UsageEnvironment& env):FramedSource(env)
{
    if(referenceCount == 0)
    {

    }
    this->camera = new Camera(0);
    this->camera->initCamera();
    ++referenceCount;
    encoder = new x264Encoder(this->camera->getWidth(), this->camera->getHeight() , this->camera->getFps());
    encoder->initilize();
    if(eventTriggerId == 0)
    {
        eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
    }
}


LiveSourceWithx264::~LiveSourceWithx264(void)
{
    --referenceCount;
    delete (this->camera);
    encoder->unInitilize();
    envir().taskScheduler().deleteEventTrigger(eventTriggerId);
    eventTriggerId = 0;
}

void LiveSourceWithx264::encodeNewFrame()
{
        this->camera->captureNewFrame();
        // Got new image to stream
        encoder->encodeFrame(this->camera->getFrame());
        // Take all nals from encoder output queue to our input queue
        while(encoder->isNalsAvailableInOutputQueue() == true)
        {
            x264_nal_t nal = encoder->getNalUnit();
            nalQueue.push(nal);
        }
}

void LiveSourceWithx264::deliverFrame0(void* clientData)
{
    ((LiveSourceWithx264*)clientData)->deliverFrame();
}

void LiveSourceWithx264::doGetNextFrame()
{
    if(nalQueue.empty() == true)
    {
        encodeNewFrame();
        gettimeofday(&currentTime,NULL);
        deliverFrame();
    }
    else
    {
        deliverFrame();
    }
}

void LiveSourceWithx264::deliverFrame()
{
    if(!isCurrentlyAwaitingData()) return;
    x264_nal_t nal = nalQueue.front();
    nalQueue.pop();
    assert(nal.p_payload != NULL);
    // You need to remove the start code which is there in front of every nal unit.  
    // the start code might be 0x00000001 or 0x000001. so detect it and remove it. pass remaining data to live555    
    int trancate = 0;
    if (nal.i_payload >= 4 && nal.p_payload[0] == 0 && nal.p_payload[1] == 0 && nal.p_payload[2] == 0 && nal.p_payload[3] == 1 )
    {
        trancate = 4;
    }
    else
    {
        if(nal.i_payload >= 3 && nal.p_payload[0] == 0 && nal.p_payload[1] == 0 && nal.p_payload[2] == 1 )
        {
            trancate = 3;
        }
    }

    if(nal.i_payload-trancate > fMaxSize)
    {
        fFrameSize = fMaxSize;
        fNumTruncatedBytes = nal.i_payload-trancate - fMaxSize;
    }
    else
    {
        fFrameSize = nal.i_payload-trancate;
    }
    fPresentationTime = currentTime;
    memmove(fTo,nal.p_payload+trancate,fFrameSize);
    FramedSource::afterGetting(this);
}  