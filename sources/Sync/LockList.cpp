#include "Sync/LockList.hpp"

LockList::LockList(unsigned int count_ , unsigned int timeout_)
{
  this->_count        = count_;
  this->_timeout      = timeout_;
  this->_lockedCount  = 0;
  this->_locked       = true;

  if (this->_count == 1)
    logger::log(WARNING_SYNC_USELESS , logger::logType::WARNING);
}
void LockList::notifyLocker()
{
  std::unique_lock<std::mutex> lck(_mutexLocker);
  this->_conditionLocker.notify_all();
  lck.unlock();
}

void LockList::waitLockee()
{
  std::unique_lock<std::mutex> lck(_mutexLocker);
  while (this->_lockedCount < this->_count) {
    if (this->_conditionLocker.wait_for(lck , std::chrono::milliseconds(this->_timeout)) == std::cv_status::timeout) {
      logger::log(WARNING_SYNC_TIMEOUT , logger::logType::WARNING);
      break;
    }
  }
  lck.unlock();
}

void LockList::wakeUp()
{
  std::unique_lock<std::mutex> lckRegister(_mutexRegister);
  std::unique_lock<std::mutex> lck(_mutexLockee);

  this->_locked = false;
  this->_conditionLockee.notify_all();
  lck.unlock();
  while (this->_lockedCount > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  lckRegister.unlock();
}

void LockList::lock()
{
  std::unique_lock<std::mutex> lckRegister(_mutexRegister);
  std::unique_lock<std::mutex> lck(_mutexLockee);

  this->_locked = true;
  this->_lockedCount++;
  lckRegister.unlock();
  this->notifyLocker();
  while (this->_locked == true)
    this->_conditionLockee.wait(lck);
  this->_lockedCount--;
}
