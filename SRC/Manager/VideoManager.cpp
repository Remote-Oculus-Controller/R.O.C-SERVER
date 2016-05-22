#include "Manager/VideoManager.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

VideoManager::VideoManager()
{
  logger::log(START_VIDEOMANAGER , logger::logType::INFO);
  this->_ready = false;
  init();
  this->_isAlive = true;
  this->_isAsyncRunning = false;
}

VideoManager::~VideoManager()
{
  std::unique_lock<std::mutex> lock(this->_lock);

  logger::log(INFO_WAIT_SYNC_JOB , logger::logType::INFO);
  this->_isAlive = false;

  while (this->_isAsyncRunning)
    this->_condition.wait(lock);

  this->uninit();
  logger::log(STOP_VIDEOMANAGER , logger::logType::SUCCESS);
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

  this->_camerasCount = configuration::camera_count;
  this->_timeout      = configuration::timeout;

  for (unsigned int i = 0 ; i < this->_camerasCount ; i++) {
    try
    {
      Camera * camera = new Camera(i);
      if (camera->initCamera() == false)
      {
        logger::log(ERROR_CAMERAS_INIT , logger::logType::FAILURE);
        this->uninit();
        return false;
      }
      this->_cameras.push_back(camera);
    }

    catch ( cv::Exception & e )
    {
      logger::log(ERROR_CAMERAS_OPEN , logger::logType::FAILURE);
      return false;
    }
  }
  this->_lockList = new LockList(this->_camerasCount , configuration::timeout);
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
  this->_isAsyncRunning = true;
  std::unique_lock<std::mutex> lock(this->_lock);
  lock.unlock();
  logger::log(SUCCESS_SYNC_JOB , logger::logType::SUCCESS);
  while (true && this->_isAlive)
  {
    lock.lock();
    this->grabAll();
    this->retrieveAll();
    lock.unlock();
    this->_lockList->waitLockee();
    lock.lock();
    this->flipAll();
    lock.unlock();
    this->_lockList->wakeUp();
  }
  logger::log(STOP_SYNC_JOB , logger::logType::SUCCESS);
  this->_isAsyncRunning = false;
  this->_condition.notify_all();
}

void VideoManager::waitSync()
{
  this->_lockList->lock();
}
