#include <mutex>
#include <iostream>
#include <condition_variable>
#include <chrono>

#include "Logger/Logger.hpp"
#include "Parser/ConfigParser.hpp"

class LockList
{
  public:

    LockList(unsigned int count_ , unsigned int timeout_);
    void wakeUp();
    void lock();
    void notifyLocker();
    void waitLockee();
    unsigned int getCount();
    bool isLocked();

  private:

    std::mutex                 _mutexLockee;
    std::condition_variable    _conditionLockee;

    std::mutex                 _mutexLocker;
    std::condition_variable    _conditionLocker;

    std::mutex                 _mutexRegister;
    std::condition_variable    _conditionRegister;

    unsigned int               _count;
    unsigned int               _timeout;
    volatile unsigned int      _lockedCount;
    volatile bool              _locked;
};
