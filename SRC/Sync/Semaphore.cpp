#include "Sync/Semaphore.hpp"

Semaphore::Semaphore(int count_) : _count{count_}
{}

void Semaphore::notify()
{
  unique_lock<mutex> lck(_mtx);
  ++_count;
  _cv.notify_one();
}

void Semaphore::wait()
{
  unique_lock<mutex> lck(_mtx);
  while(_count == 0)
  {
      _cv.wait(lck);
  }
  --_count;
}
