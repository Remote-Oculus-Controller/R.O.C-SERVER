#include "Manager/Cleanup.hpp"

std::condition_variable Cleanup::condition;
std::mutex Cleanup::lock;

void cleanup(int signal)
{
    std::unique_lock<std::mutex> lock(Cleanup::lock);
    Cleanup::condition.notify_all();
}
