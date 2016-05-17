#include <mutex>
#include <condition_variable>

class WaitList
{
  public:

    WaitList(int count_ = 0 , int timeout_ = 0);
    void spawn();
    void wait();

  private:

    std::mutex _lockerMtx;
    std::condition_variable _lockerCv;

    std::mutex _lockeeMtx;
    std::condition_variable _lockeeCv;

    int   _count;
    int   _timeout;
    bool  _locked;
};
