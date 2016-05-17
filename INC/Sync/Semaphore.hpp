#include <mutex>
#include <condition_variable>
using namespace std;

class Semaphore
{
  public:
    Semaphore(int count_ = 0);
    void notify();
    void wait();

  private:
    mutex _mtx;
    condition_variable _cv;
    int _count;
};
