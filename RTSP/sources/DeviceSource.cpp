#include "DeviceSource.hh"
#include <GroupsockHelper.hh> // for "gettimeofday()"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

//static uint8_t *buf = (uint8_t*)malloc(102400);
static uint8_t buf[8192];
int upp_stream;
//static uint8_t *bufPtr = buf;

DeviceSource*
DeviceSource::createNew(UsageEnvironment& env)
{

  return new DeviceSource(env);
}

EventTriggerId DeviceSource::eventTriggerId = 0;

unsigned DeviceSource::referenceCount = 0;

DeviceSource::DeviceSource(UsageEnvironment& env):FramedSource(env) 
{ 

  if (referenceCount == 0) 
  {

      upp_stream = open("/dev/upp",O_RDWR);

  }
  ++referenceCount;

  if (eventTriggerId == 0) 
  {
    eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
  }
}

DeviceSource::~DeviceSource(void) {
  --referenceCount;
  envir().taskScheduler().deleteEventTrigger(eventTriggerId);
  eventTriggerId = 0;

  if (referenceCount == 0) 
  {

  }
}

int loop_count;

void DeviceSource::doGetNextFrame() 
{

    //for (loop_count=0; loop_count < 13; loop_count++)
    //{
        read(upp_stream,buf, 8192);

        //bufPtr+=8192;

    //}
    deliverFrame();

}

void DeviceSource::deliverFrame0(void* clientData) 
{
  ((DeviceSource*)clientData)->deliverFrame();
}

void DeviceSource::deliverFrame() 
{


  if (!isCurrentlyAwaitingData()) return; // we're not ready for the data yet

  u_int8_t* newFrameDataStart = (u_int8_t*) buf;             //(u_int8_t*) buf; //%%% TO BE WRITTEN %%%
  unsigned newFrameSize = sizeof(buf); //%%% TO BE WRITTEN %%%

  // Deliver the data here:
  if (newFrameSize > fMaxSize) {
    fFrameSize = fMaxSize;
    fNumTruncatedBytes = newFrameSize - fMaxSize;
  } else {
    fFrameSize = newFrameSize;
  }
  gettimeofday(&fPresentationTime, NULL); 
  memmove(fTo, newFrameDataStart, fFrameSize);
  FramedSource::afterGetting(this);
}