#include "Singletons/VideoManagerSingleton.hpp"

VideoManager * VideoManagerSingleton::getInstance() {
    static VideoManager * instance = NULL;

    if (instance == NULL)
        instance = new VideoManager();
    return instance;
}
