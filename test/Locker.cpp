#include "Locker.hpp"

Locker::Locker(int count_) : _count{count_}
{
  locked = true;
}

void Locker::notify()
{
  unique_lock<mutex> lck(_mtx);
  _cv.notify_one();
}

void Locker::notify_all()
{
  unique_lock<mutex> lck(_mtx);
  _locked = false;
  _cv.notify_all();
}

void Locker::wait()
{
  unique_lock<mutex> lck(_mtx);
  _locked = true;
  _count++;
  while(_locked == true)
  {
      _cv.wait(lck);
  }
  --_count;

.}

// MISE EN ATTENTE SUR WAITLIST -> NOTIFICATION LOCKER -> SI TOUS LES LOCKEE SONT LA -> UNLOCK WAITLIST
