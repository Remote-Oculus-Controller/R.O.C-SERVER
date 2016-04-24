#include "Manager/VideoManager.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

VideoManager::VideoManager()
{
  this->_watcher = 0;
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
  YAMLParser parser = YAMLParser(VIDEO_MANAGER_CONFIG_FILE , FileStorage::READ);
  if (parser.isOpened() == false)
    return false;

  this->_camerasCount = parser.getValueOf("camera_count");
  this->_treshold     = parser.getValueOf("treshold");
  this->_timeout      = 1000 / parser.getValueOf("fps");

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
  this->_cameras[id]->grabFrame();
  this->_cameras[id]->retrieveFrame();
  return this->_cameras[id]->getFrame();
}

//====================================================
// GRAB ALL FRAMES TO SYNC CAMERAS
//====================================================

bool VideoManager::grab()
{
  unsigned int error = 0;
  for (unsigned int i = 0 ; i < this->_cameras.size() ; i++) {
    if (this->_cameras[i]->grabFrame() == false)
      error = error + 1;
  }
  if (error)
    return false;
  return true;
}
