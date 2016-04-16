#ifndef VIDEOMANAGERSINGLETON_HPP
#define VIDEOMANAGERSINGLETON_HPP

#include "Manager/VideoManager.hpp"

class VideoManagerSingleton
{
  public:
    static VideoManager * getInstance();
}

#endif // VIDEOMANAGERSINGLETON_HPP
