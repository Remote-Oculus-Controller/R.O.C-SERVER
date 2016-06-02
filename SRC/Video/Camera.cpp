#include <iostream>
#include "Video/Camera.hpp"

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

Camera::Camera(int id)
{
	this->_id = id;
	this->_camera = new cv::VideoCapture(this->_id);
}


Camera::~Camera()
{
	if (this->_camera->isOpened())
		this->_camera->release();
	delete (this->_camera);
	logger::log(STOP_CAMERA , logger::logType::SUCCESS);
}

//====================================================
// GETTERS
//====================================================

int Camera::getId() const
{
	return this->_id;
}


Mat & Camera::getFrame()
{
	return this->_frontFrame;
}

//====================================================
// SETTERS
//====================================================


//====================================================
// FONCTIONS GENERALES POUR LA CAMERA
//====================================================

bool Camera::initCamera()
{
	this->_camera->open(this->_id);
	if (this->_camera->isOpened() == false)
		return false;
  if (this->initResolutions() == false)
    return false;
    return true;
}

bool Camera::retrieveFrame()
{
	return this->_camera->retrieve(this->_backFrame);
}

bool Camera::grabFrame()
{
	return this->_camera->grab();
}

bool Camera::flipFrame()
{
	this->_frontFrame = this->_backFrame.clone();
}

bool Camera::reOpenCamera()
{
	delete (this->_camera);
	this->_camera = new cv::VideoCapture(this->_id);
    if (this->_camera == NULL)
        return false;
    return true;
}

bool Camera::set(int propId , double value)
{
	return this->_camera->set(propId , value);
}

//===================================================
// FONCTIONS MASQUEES D'INITIALISATION
//===================================================

bool Camera::initResolutions()
{
		this->_camera->set(cv::CAP_PROP_FRAME_WIDTH, configuration::width);
		this->_camera->set(cv::CAP_PROP_FRAME_HEIGHT, configuration::height);
		this->_camera->set(cv::CAP_PROP_FPS, configuration::fps);

		this->_width = this->_camera->get(cv::CAP_PROP_FRAME_WIDTH);
		this->_height = this->_camera->get(cv::CAP_PROP_FRAME_HEIGHT);
		this->_fps = this->_camera->get(cv::CAP_PROP_FPS);

		if (this->_width != configuration::width)
			logger::log(ERROR_CAMERA_WIDTH , logger::logType::FAILURE);
		else
			logger::log(SUCCESS_WIDTH , logger::logType::SUCCESS);
		if (this->_height != configuration::height)
			logger::log(ERROR_CAMERA_HEIGHT , logger::logType::FAILURE);
		else
			logger::log(SUCCESS_HEIGHT , logger::logType::SUCCESS);
		if (this->_fps != configuration::fps)
			logger::log(ERROR_CAMERA_FPS , logger::logType::FAILURE);
		else
			logger::log(SUCCESS_FPS , logger::logType::SUCCESS);


		logger::log(INFO_CONFIG("Camera width" , this->_width), logger::logType::INFO);
		logger::log(INFO_CONFIG("Camera height" , this->_height), logger::logType::INFO);
		logger::log(INFO_CONFIG("Camera fps" , this->_fps), logger::logType::INFO);

		return true;
}

int Camera::getWidth()
{
	return this->_width;
}

int Camera::getHeight()
{
	return this->_height;
}

int Camera::getFps()
{
  return this->_fps;
}
