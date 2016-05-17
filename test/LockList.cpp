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
  std::cout << "Notify locker" << std::endl;
  this->_conditionLocker.notify_all();
}

void LockList::waitLockee()
{
  std::unique_lock<std::mutex> lck(_mutexLocker);
std::cout << "Wait lockee" << std::endl;
  while (this->_lockedCount < this->_count)
    this->_conditionLocker.wait(lck);
}

void LockList::wakeUp()
{
  std::unique_lock<std::mutex> lck(_mutexLockee);

  std::cout << "Wake Up" << std::endl;
  this->_locked = false;
  this->_conditionLockee.notify_all();
}

void LockList::lock()
{
  std::unique_lock<std::mutex> lck(_mutexLockee);
  this->_locked = true;
  std::cout << "Lock" << std::endl;
  this->_lockedCount++;
  this->notifyLocker();
  while (this->_locked == true)
    this->_conditionLockee.wait(lck);
  this->_lockedCount--;
}
