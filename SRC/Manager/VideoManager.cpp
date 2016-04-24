#include "Manager/VideoManager.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

VideoManager::VideoManager()
{
  this->_ready = this->init();
}

VideoManager::~VideoManager()
{
  this->uninit();
}

//====================================================
// GETTER ON THE STATE OF THE MANAGER READY OR NOT
//====================================================

bool VideoManager::isReady()
{
  return this->_ready;
}

//====================================================
// FUNCTION INIT (CALLED AUTOMATICALLY)
//====================================================

bool VideoManager::init()
{
  unsigned int tmpCount;
  unsigned int tmpTreshold;
  unsigned int tmpTimeout;

  YAMLParser parser = YAMLParser(VIDEO_MANAGER_CONFIG_FILE , FileStorage::READ);
  if (parser.isOpened() == false)
    return false;

  tmpCount = parser.getValueOf("camera_count");
  tmpTreshold = parser.getValueOf("treshold");
  tmpTimeout = parser.getValueOf("fps");

  if (tmpCount == 0 || tmpCount > 4 || tmpTimeout == 0)
    return false;

  this->_camerasCount = tmpCount;
  this->_treshold     = tmpTreshold;
  this->_timeout      = 1000 / tmpTimeout;

  for (unsigned int i = 0 ; i < this->_camerasCount ; i++) {
    Camera * camera = new Camera(i);
    if (camera->initCamera() == false)
    {
      this->uninit();
      return false;
    }
    this->_cameras.push_back(camera);
  }
}

//====================================================
// FUNCTION UNINIT (CALLED AUTOMATICALLY)
//====================================================

bool VideoManager::uninit()
{
  for (unsigned int i = 0 ; i < this->_cameras.size() ; i++) {
    delete this->_cameras[i];
  }
}

//====================================================
// RETURN THE BUFFERED FRAME OF A CAMERA
//====================================================

cv::Mat & VideoManager::queryFrame(unsigned int id)
{
  return this->_cameras[id]->getFrame();
}

//====================================================
// GRAB ALL FRAMES TO SYNC CAMERAS
//====================================================

bool VideoManager::grab(unsigned int id)
{
    if (id < this->_cameras.size())
      return this->_cameras[id]->grabFrame();
    return false;
}

bool VideoManager::retrieve(unsigned int id)
{
  if (id < this->_cameras.size())
    return this->_cameras[id]->retrieveFrame();
  return false;
}
