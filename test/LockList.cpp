#include "LockList.hpp"

// VEROUILLAGE LISTE
// AJOUT SUR LA LISTE D'ATTENTE
// NOTIFICATION SUR AJOUT
// SI TOUT LES CLIENTS SONT PRESENTS UNLOCK
// EMPECHER UN AJOUT PENDANT UN UNLOCK

LockList::LockList(unsigned int count_ , unsigned int timeout_)
{
  this->_count        = count_;
  this->_timeout      = timeout_;
  this->_lockedCount  = 0;
  this->_locked       = true;
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
  while (this->_lockedCount < this->_count)
    this->_conditionLocker.wait(lck);
  lck.unlock();
}

void LockList::wakeUp()
{
  std::unique_lock<std::mutex> lckRegister(_mutexRegister);
  std::unique_lock<std::mutex> lck(_mutexLockee);

  this->_locked = false;
  this->_conditionLockee.notify_all();
  lck.unlock();
  while (this->_lockedCount > 0);
  lckRegister.unlock();
}

void LockList::lock()
{
  std::unique_lock<std::mutex> lckRegister(_mutexRegister);
  std::unique_lock<std::mutex> lck(_mutexLockee);

  this->_locked = true;
  this->_lockedCount++;
  lckRegister.unlock();
  std::cout << this->_lockedCount  << std::endl;
  this->notifyLocker();
  while (this->_locked == true)
    this->_conditionLockee.wait(lck);
  this->_lockedCount--;
  std::cout << this->_lockedCount  << std::endl;
}
