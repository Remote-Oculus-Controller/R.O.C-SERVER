#include "Logger/Logger.hpp"
#include "Logger/colors.hpp"

namespace logger
{
    void log(std::string message , logType type)
    {
      Logger * instance = Logger::getInstance();
      if (instance)
        instance->pushLog(instance->buildLog(message , type));
    }

    void waitSync()
    {
      Logger * instance = Logger::getInstance();
      if (instance)
        instance->sync();
    }

    Logger::Logger()
    {
      this->isAlive = true;
      this->start = std::chrono::steady_clock::now();
      std::thread runner(&Logger::run, this);
      runner.detach();
    }


    Logger * Logger::getInstance()
    {
      static Logger * instance;

      if (instance == NULL)
        instance = new Logger();
      return instance;
    }

    std::string Logger::buildLog(std::string message , logType type)
    {
      std::string formatedMessage;
      this->setColor(formatedMessage , type);
      this->addLogType(formatedMessage , type);
      formatedMessage += message;
      this->resetColor(formatedMessage);
      return formatedMessage;
    }

    void Logger::pushLog(std::string formatedMessage)
    {
      std::unique_lock<std::mutex> lock(this->queueLock);
      this->messageQueue.push(formatedMessage);
      this->condition.notify_all();
    }

    void Logger::sync()
    {
      std::unique_lock<std::mutex> lock(this->syncLock);
      while (!this->messageQueue.empty()) {
        this->conditionSync.wait_for(lock , std::chrono::milliseconds(100));
      }
    }

    void Logger::run()
    {
      std::unique_lock<std::mutex> lock(this->queueLock);
      std::unique_lock<std::mutex> lockSync(this->syncLock);
      lockSync.unlock();
      while (true)
      {
        while (this->messageQueue.empty())
          this->condition.wait(lock);
        lockSync.lock();
        while (!this->messageQueue.empty())
        {
          std::cout << this->messageQueue.front() << std::endl;
          this->messageQueue.pop();
        }
        this->conditionSync.notify_all();
        lockSync.unlock();
      }
    }

    void Logger::addLogType(std::string & message , logType type)
    {
      std::stringstream ss;
      std::string strType;

      switch(type)
      {
        case logType::PRIORITY:
          strType = "[INFO]";
        break;
        case logType::INFO:
          strType = "[INFO]";
        break;
        case logType::SUCCESS:
          strType = "[SUCCESS]";
        break;
        case logType::WARNING:
          strType = "[WARNING]";
        break;
        case logType::FAILURE:
          strType = "[FAILURE]";
        break;
        default:
          strType = "[UKNOWN]";
        break;
      }
      ss << std::setw(15) << std::setfill(' ') << std::left << strType;
      message += ss.str();
    }

    void Logger::setColor(std::string & message , logType type)
    {

      switch(type)
      {
        case logType::PRIORITY:
          message += MAGENTA;
        break;
        case logType::INFO:
          message += BLUE;
        break;
        case logType::SUCCESS:
          message += GREEN;
        break;
        case logType::WARNING:
          message += YELLOW;
        break;
        case logType::FAILURE:
          message += RED;
        break;
        default:
        break;
      }
    }

    void Logger::resetColor(std::string & message)
    {
      message += RESET;
    }

    void Logger::addTimeStamp(std::string & message)
    {
      std::stringstream ss;
      std::stringstream input;
      auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - this->start).count();
      input << time;
      ss << std::setw(8) << std::setfill(' ') << std::left << '[' + input.str() + ']';
      std::string timeStamp = ss.str();
      message.insert(0 , timeStamp);
    }
}
