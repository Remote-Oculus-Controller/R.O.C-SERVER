#ifndef CLEARNUP_HPP
#define CLEARNUP_HPP

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <mutex>
#include <condition_variable>


void cleanup(int signal);

class Cleanup
{
  public:
    static std::condition_variable condition;
    static std::mutex lock;
};

#define ROC_DEFER_CLEANUP signal(SIGINT , cleanup);

#endif // CLEARNUP_CPP
