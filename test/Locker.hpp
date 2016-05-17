#include <mutex>
#include <condition_variable>
using namespace std;

class Locker
{
  public:

    Locker(int count_ = 0);
    void notify();
    void notify_all();
    void wait();

  private:

    mutex _mtx;
    condition_variable _cv;
    int _count;
    volatile bool _locked;
};
