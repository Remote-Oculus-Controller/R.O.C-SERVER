#include <iostream>
#include <thread>
#include "LockList.hpp"

LockList list(4 , 0);

void lock(int Id)
{
  unsigned int i = 0;
  std::cout << "Starting locker !" << std::endl;
  while (i < 999999)
  {
    list.waitLockee();
    list.wakeUp();
    i++;
  }

}

void print(int Id)
{
  unsigned int i = 0;
  while (i < 999999)
  {
    std::cout << "(" << i << ")" << "Registering : " << Id << std::endl;
    list.lock();
    std::cout << "(" << i << ")" << "Running : " << Id << std::endl;
    i++;
  }
}

int main(int argc, char const *argv[]) {

  std::thread locker(lock , 1);
  std::thread first(print, 1);
  std::thread second(print, 2);
  std::thread third(print, 3);
  std::thread fourth(print, 4);

  locker.join();
  first.join();
  second.join();
  third.join();
  fourth.join();
  return 0;
}
