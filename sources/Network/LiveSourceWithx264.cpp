#include "Network/LiveSourceWithx264.hpp"

LiveSourceWithx264 *LiveSourceWithx264::createNew(UsageEnvironment &env , VideoManager * manager , unsigned int id) {
    return new LiveSourceWithx264(env, manager , id);
}

EventTriggerId LiveSourceWithx264::eventTriggerId = 0;

unsigned LiveSourceWithx264::referenceCount = 0;

LiveSourceWithx264::LiveSourceWithx264(UsageEnvironment &env , VideoManager * manager , unsigned int id) : FramedSource(env) {
    if (referenceCount == 0) {

    }

    this->_manager = manager;
    this->_id = id;
    ++referenceCount;
    encoder = new x264Encoder(this->_manager->getWidthById(this->_id),
                              this->_manager->getHeightById(this->_id),
                              this->_manager->getFpsById(this->_id));
    encoder->initilize();
    if (eventTriggerId == 0) {
        eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
    }
}


LiveSourceWithx264::~LiveSourceWithx264(void) {
    --referenceCount;
    encoder->unInitilize();
    envir().taskScheduler().deleteEventTrigger(eventTriggerId);
    eventTriggerId = 0;
}


void LiveSourceWithx264::fetchNewFrame()
{
  this->_manager->waitSync();
}

void LiveSourceWithx264::processNewFrame()
{
  this->_manager->getProcessingWrapper().apply(this->_manager->getFrame(this->_id));
}

void LiveSourceWithx264::encodeNewFrame()
{
        encoder->encodeFrame(this->_manager->getFrame(this->_id));
        while(encoder->isNalsAvailableInOutputQueue() == true)
        {
            x264_nal_t nal = encoder->getNalUnit();
            nalQueue.push(nal);
        }
}

void LiveSourceWithx264::deliverFrame0(void *clientData) {
    ((LiveSourceWithx264 *) clientData)->deliverFrame();
}

void LiveSourceWithx264::doGetNextFrame() {
    if (nalQueue.empty() == true) {
        fetchNewFrame();
        processNewFrame();
        encodeNewFrame();
        gettimeofday(&currentTime, NULL);
        deliverFrame();
    }
    else {
        deliverFrame();
    }
}

void LiveSourceWithx264::deliverFrame() {
    if (!isCurrentlyAwaitingData()) return;
    x264_nal_t nal = nalQueue.front();
    nalQueue.pop();
    assert(nal.p_payload != NULL);

    int trancate = 0;
    if (nal.i_payload >= 4 && nal.p_payload[0] == 0 && nal.p_payload[1] == 0 && nal.p_payload[2] == 0 &&
        nal.p_payload[3] == 1) {
        trancate = 4;
    }
    else {
        if (nal.i_payload >= 3 && nal.p_payload[0] == 0 && nal.p_payload[1] == 0 && nal.p_payload[2] == 1) {
            trancate = 3;
        }
    }

    if (nal.i_payload - trancate > fMaxSize) {
        fFrameSize = fMaxSize;
        fNumTruncatedBytes = nal.i_payload - trancate - fMaxSize;
    }
    else {
        fFrameSize = nal.i_payload - trancate;
    }
    fPresentationTime = currentTime;
    memmove(fTo, nal.p_payload + trancate, fFrameSize);
    FramedSource::afterGetting(this);
}
