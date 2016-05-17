#include "Manager/VideoManager.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

VideoManager::VideoManager()
{
  this->_ready = false;
  init();
}

VideoManager::~VideoManager()
{
  this->uninit();
  this->_ready = false;
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

  if (this->_ready == true)
    return true;

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
  this->_lockList = new LockList(this->_camerasCount , 0);
  if (!this->_lockList)
    return false;
  this->_ready = true;
  return this->_ready;
}

//====================================================
// FUNCTION UNINIT (CALLED AUTOMATICALLY)
//====================================================

bool VideoManager::uninit()
{
  for (unsigned int i = 0 ; i < this->_cameras.size() ; i++) {
    delete this->_cameras[i];
  }
  this->_cameras.clear();
  this->_ready = false;
  return true;
}

//====================================================
// GRAB RETRIEVE FLIP AND RETURN THE BUFFERED FRAME OF A CAMERA
//====================================================

cv::Mat & VideoManager::queryFrame(unsigned int id)
{
  this->_lockList->lock();
  this->_cameras[id]->grabFrame();
  this->_cameras[id]->retrieveFrame();
  this->_cameras[id]->flipFrame();
  return this->_cameras[id]->getFrame();
}

//====================================================
// RETURN THE BUFFERED FRAME OF A CAMERA
//====================================================

cv::Mat & VideoManager::getFrame(unsigned int id)
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

//====================================================
// GRAB ALL FRAMES TO SYNC CAMERAS
//====================================================

bool VideoManager::retrieve(unsigned int id)
{
  if (id < this->_cameras.size())
    {
      this->_cameras[id]->flipFrame();
      return this->_cameras[id]->retrieveFrame();
    }
  return false;
}

int VideoManager::getHeightById(unsigned int id)
{
  if (id < this->_cameras.size())
    return this->_cameras[id]->getHeight();
  return -1;
}


int VideoManager::getWidthById(unsigned int id)
{
  if (id < this->_cameras.size())
    return this->_cameras[id]->getWidth();
  return -1;
}


int VideoManager::getFpsById(unsigned int id)
{
  if (id < this->_cameras.size())
    return this->_cameras[id]->getFps();
  return -1;
}

void VideoManager::grabAll()
{
  for(std::vector<Camera *>::iterator it = this->_cameras.begin(); it != this->_cameras.end(); ++it) {
    (*it)->grabFrame();
  }
}

void VideoManager::retrieveAll()
{
  for(std::vector<Camera *>::iterator it = this->_cameras.begin(); it != this->_cameras.end(); ++it) {
    (*it)->retrieveFrame();
  }
}

void VideoManager::flipAll()
{
  for(std::vector<Camera *>::iterator it = this->_cameras.begin(); it != this->_cameras.end(); ++it) {
    (*it)->flipFrame();
  }
}

bool VideoManager::run()
{
  std::thread runner(&VideoManager::loop, this);
  runner.detach();
}

bool VideoManager::loop()
{
  while (true)
  {
    this->grabAll();
    this->retrieveAll();
    this->_lockList->waitLockee();
    this->flipAll();
    this->_lockList->wakeUp();
  }
}

void VideoManager::waitSync()
{
  this->_lockList->lock();
}
