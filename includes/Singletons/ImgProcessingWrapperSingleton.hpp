#ifndef IMGPROCESSINGWRAPPERSINGLETON_HPP
#define IMGPROCESSINGWRAPPERSINGLETON_HPP

#include "Processing/ImgProcessingWrapper.hpp"

class ImgProcessingWrapperSingleton {
  public:
    static ImgProcessingWrapper * getInstance();
};

#endif // IMGPROCESSINGWRAPPERSINGLETON_HPP
