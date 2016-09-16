#ifndef NETWORKINTERPRETOR_HPP
#define NETWORKINTERPRETOR_HPP

#include <thread>
#include <mutex>

#include "Manager/Manager.hpp"
#include "Parser/ConfigParser.hpp"
#include "Processing/ImgProcessing.hpp"
#include "Processing/EyeDetect.hpp"
#include "Processing/UpperBodyDetect.hpp"
#include "Processing/LowerBodyDetect.hpp"
#include "Processing/FullBodyDetect.hpp"
#include "proto.pb.h"
#include "video.pb.h"


#define COMMAND 0x1
#define DATA    0x2
#define ERROR   0x3

#define NONE    0x0
#define VCLIENT 0x1
#define VSERVER 0x2
#define VCTRL   0x4
#define ALL     0x7

class Manager;

class NetworkInterpretor
{
  public:

    NetworkInterpretor(Manager * parent);
    ~NetworkInterpretor();

    void run();

  private:

    rocproto::Packet * getMessage();
    void putMessage(rocproto::Packet * message);

    bool isValid(rocproto::Packet * message);
    bool needRerouting(rocproto::Packet * message);

    void handlePacket(rocproto::Packet * message);

    void connectionQuery(rocproto::Packet * message);
    void clearQuery();
    void cannyQuery(rocproto::Packet * message);
    void faceQuery(rocproto::Packet * message);
    void zoomQuery(rocproto::Packet * message);
    void eyeQuery(rocproto::Packet * message);
    void upperBodyQuery(rocproto::Packet * message);
    void lowerBodyQuery(rocproto::Packet * message);
    void fullBodyQuery(rocproto::Packet * message);

    void runner();
    void waitRunner();

    unsigned createMask(unsigned , unsigned);
    unsigned createHeader(unsigned type , unsigned from , unsigned to);

  private:

    std::mutex              _lockMain;
    std::condition_variable _conditionMain;

    std::mutex              _lockRead;
    std::condition_variable _conditionRead;

    Manager *               _parent;

    bool                    _keepAlive;
    bool                    _isAsyncRunning;

};

#endif // NETWORKINTERPRETOR_HPP
