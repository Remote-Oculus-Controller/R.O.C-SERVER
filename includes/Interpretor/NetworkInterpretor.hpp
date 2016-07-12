#ifndef NETWORKINTERPRETOR_HPP
#define NETWORKINTERPRETOR_HPP

#include <thread>
#include <mutex>

#include "Manager/Manager.hpp"

#include "proto.pb.h"
#include "video.pb.h"

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

    void connectionQuery();
    void cannyQuery(protocol::Packet * message);
    void faceQuery(protocol::Packet * message);

    void runner();
    void waitRunner();

    unsigned createMask(unsigned , unsigned);

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
