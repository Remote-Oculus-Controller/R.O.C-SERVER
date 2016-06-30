#include "Singletons/ImgProcessingWrapperSingleton.hpp"

ImgProcessingWrapper * ImgProcessingWrapperSingleton::getInstance()
{
  static ImgProcessingWrapper * instance = NULL;

  if (instance == NULL)
    instance = new ImgProcessingWrapper();
  return instance;
}
