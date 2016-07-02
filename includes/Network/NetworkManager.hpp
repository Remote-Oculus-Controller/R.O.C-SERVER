#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <thread>
#include <mutex>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "proto.pb.h"

#include "Manager/Manager.hpp"
#include "Network/TcpServer.hpp"
#include "Network/NetworkInterface.hpp"
#include "Logger/Logger.hpp"


class Manager;

#define TCP_BUFFER_SIZE 512

class NetworkManager {
  public:

    NetworkManager(Manager * parent , unsigned short port);
    ~NetworkManager();
    void run();
    bool init();

  protected:

    void runner();
    void waitRunner();

  protected:

    Manager *   _parent;
    TcpServer * _server;
    char        _buffer[TCP_BUFFER_SIZE];
    bool        _run;
    bool        _isAsyncRunning;
    std::mutex  _lock;
    std::condition_variable _condition;

};

#endif // NETWORKMANAGER_HPP
