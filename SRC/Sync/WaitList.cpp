#include "Sync/WaitList.hpp"

WaitList::WaitList(int count_ , int timeout_)
{
  this->_count    = count_;
  this->_timeout  = timeout_;
}

void WaitList::wait()
{
  std::unique_lock<std::mutex> lockee(_lockeeMtx);
  std::unique_lock<std::mutex> locker(_lockeeMtx);

  _count -= 1;
  _lockerCv.notify_one();
  while (_locked == true)
  {
    _lockeeCv.wait(lockee);
  }
  _count += 1;
}
void WaitList::spawn()
{
  std::unique_lock<std::mutex> locker(_lockeeMtx);
  std::unique_lock<std::mutex> lockee(_lockerMtx);

  while (_count != 0)
  {
    _lockerCv.wait(locker);
  }

  _locked = false;
  _lockeeCv.notify_all();
}
