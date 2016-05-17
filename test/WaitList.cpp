#include <iostream>
#include "WaitList.hpp"

WaitList::WaitList(int count_ )
{
  _count = count_;

  lockee = new Semaphore(_count);
  locker = new Semaphore(1);
}

void WaitList::wait()
{
  std::cout << "Notify waitlist of new waiter" << std::endl;
  locker->notify();
  lockee->wait();
}

void WaitList::spawn()
{
  std::cout << "Waiting for notifications" << std::endl;
  locker->wait();
  lockee->notify_all();
}
