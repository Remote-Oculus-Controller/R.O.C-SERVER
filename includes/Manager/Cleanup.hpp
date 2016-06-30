#ifndef CLEARNUP_HPP
#define CLEARNUP_HPP

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include "Manager/Manager.hpp"

void cleanup(int signal);

class Cleanup
{
  public:
    static volatile sig_atomic_t flag;
};

#define ROC_DEFER_CLEANUP signal(SIGINT , cleanup);

#endif // CLEARNUP_CPP
