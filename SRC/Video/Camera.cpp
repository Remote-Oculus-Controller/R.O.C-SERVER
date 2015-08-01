#include "Video/Camera.hpp"
#include <iostream>

//====================================================
// CONSTRUCTEUR / DESTRUCTEUR
//====================================================

Camera::Camera(int id, int compression)
{
	this->_id = id;
	this->_compression = compression;
	this->_camera = new cv::VideoCapture(this->_id);
}

Camera::~Camera()
{
	if (this->_camera->isOpened())
	this->_camera->release();
	delete (this->_camera);
}

//====================================================
// GETTERS
//====================================================

int Camera::getId() const 
{
	return (this->_id);
}

int Camera::getCompression() const 
{
	return (this->_compression);
}

Mat & Camera::getFrame()
{
	return (this->_frame);
}

std::vector<unsigned char> * Camera::getCompressedFrame()
{
  return (&(this->_compressedFrame));
}

//====================================================
// SETTERS
//====================================================

void Camera::setCompression(int ratio)
{
	this->_compression = ratio;
}

//====================================================
// FONCTIONS GENERALES POUR LA CAMERA
//====================================================

bool Camera::initCamera()
{
	this->_camera->open(this->_id);
	if (this->_camera->isOpened() == false)
		return (false);
	this->_camera->set(cv::CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
	this->initCompressionParams();
	this->initResolutions();
	
}

bool Camera::captureNewFrame()
{
  this->_camera->read(this->_frame);
  return (true);
}

bool Camera::compressFrame()
{
	cv::imencode(	".jpg",
					this->_frame,
					this->_compressedFrame,
					this->_compressionParams);
}

bool Camera::upgradeQuality(int resolution, int compression)
{
	if (resolution)
	{
		if (this->_resolutionIndex < this->_widthArray.size() - 1)
		{
			this->_resolutionIndex++;
			return (true);
		}
		return (false);
	}
	return (true);
}

bool Camera::downgradeQuality(int resolution, int compression)
{
	if (resolution)
	{
		if (this->_resolutionIndex > 0)
		{
			this->_resolutionIndex--;
			return (true);
		}
		return (false);
	}
	return (true);
}

bool Camera::reOpenCamera()
{
	delete (this->_camera);
	this->_camera = new cv::VideoCapture(this->_id);
}

//===================================================
// FONCTIONS MASQUEES D'INITIALISATION
//===================================================

void Camera::initCompressionParams()
{
	this->_compressionParams.push_back(cv::IMWRITE_JPEG_QUALITY);
	this->_compressionParams.push_back(this->_compression);
}

void Camera::initResolutions()
{
	int maxResolutions;
	int defaultResolution;
	int current;

	std::fstream configFile(CONFIG_FILE, std::ios_base::in);
	configFile >> maxResolutions;
	configFile >> defaultResolution;
	for (int i = 0; i < maxResolutions; i++)
	{
		configFile >> current;
		this->_widthArray.push_back(current);
		configFile >> current;
		this->_heightArray.push_back(current);
	}
	this->_resolutionIndex = (defaultResolution - 1);
	
	this->_camera->set(cv::CAP_PROP_FRAME_WIDTH, this->_widthArray[this->_resolutionIndex]);
	this->_camera->set(cv::CAP_PROP_FRAME_HEIGHT,this->_heightArray[this->_resolutionIndex]);
	this->_camera->set(cv::CAP_PROP_FPS, 30);
	std::cout << this->_camera->get(cv::CAP_PROP_FPS) << " FPS" << std::endl;
	std::cout << this->_camera->get(cv::CAP_PROP_FRAME_WIDTH) << "x" << this->_camera->get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
}
