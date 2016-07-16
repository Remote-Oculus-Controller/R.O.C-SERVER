#ifndef NETWORKINTERPRETOR_HPP
#define NETWORKINTERPRETOR_HPP

#include <thread>
#include <mutex>

#include "Manager/Manager.hpp"
#include "Parser/ConfigParser.hpp"
#include "Processing/ImgProcessing.hpp"

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

    protocol::Packet * getMessage();
    void putMessage(protocol::Packet * message);

    bool isValid(protocol::Packet * message);
    bool needRerouting(protocol::Packet * message);

    void handlePacket(protocol::Packet * message);

    void connectionQuery(protocol::Packet * message);
    void clearQuery();
    void cannyQuery(protocol::Packet * message);
    void faceQuery(protocol::Packet * message);
    void zoomQuery(protocol::Packet * message);

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
