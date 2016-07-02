#include "Sync/Semaphore.hpp"

Semaphore::Semaphore(int count_) : _count{count_} , _capacity{count_} {
}

void Semaphore::notify(bool unique) {
    unique_lock<mutex> lck(_mtx);
    if (unique)
        _count = _capacity;
    else
        _count++;
    _cv.notify_one();
}

void Semaphore::wait(bool unique) {
    unique_lock<mutex> lck(_mtx);
    if (unique) {
        while(_count != _capacity) {
            _cv.wait(lck);
        }
        _count = 0;
    }

    else {
        while(_count == 0) {
            _cv.wait(lck);
        }
        --_count;
    }
}
