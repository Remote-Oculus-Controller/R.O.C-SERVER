#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <string>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>

#include "Logger/Logs.hpp"

namespace logger
{
  enum logType
  {
    INFO ,
    PRIORITY,
    SUCCESS ,
    WARNING ,
    FAILURE
  };


  void log(std::string message , logType type);
  class Logger
  {
    public:

      Logger();
      static Logger * getInstance();

      std::string buildLog(std::string message , logType type);
      void pushLog(std::string formatedMessage);

    private:

      void setColor(std::string & message , logType type);
      void resetColor(std::string & message);
      void addTimeStamp(std::string & message);
      void addLogType(std::string & message ,  logType type);

      void run();

      std::mutex              queueLock;
      std::condition_variable condition;
      std::queue<std::string> messageQueue;

      std::chrono::steady_clock::time_point start;
  };
}

#endif
