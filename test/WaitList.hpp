#include "Locker.hpp"

class WaitList
{
  public:

    WaitList(int count_ = 0);
    void spawn();
    void wait();

  private:

    Semaphore * lockee;
    Semaphore * locker;

    int   _count;
};
