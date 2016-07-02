#include "Manager/Cleanup.hpp"

volatile sig_atomic_t Cleanup::flag = 0;

void cleanup(int signal) {
    Cleanup::flag = 1;
}
