#include "Video/CameraV4L2.h"

CameraV4L2::CameraV4L2(char * device, int width, int height)
{
	this->_device 		= device;

	this->_width  		= width;
	this->_height 		= height;

	this->_format 	  	= V4L2_PIX_FMT_MJPEG;
	this->_grabMethod 	= 1;

	this->_brightness 	= 0;
	this->_contrast 	= 0;
	this->_saturation 	= 0;
	this->_gain 		= 0;
}

CameraV4L2::~CameraV4L2()
{
	close_v4l2(&(this->_videoIn));
}

bool CameraV4L2::init()
{
	if (init_videoIn(&(this->_videoIn), 
					this->_device, 
					this->_width, 
					this->_height, 
					this->_format, 
					this->_grabMethod) < 0)
		return (false);
	return (true);
}

bool CameraV4L2::grabFrame()
{
	if (uvcGrab(&(this->_videoIn) < 0))
		return (false);
	return (true);
}

char * CameraV4L2::getFrame(size_t * size)
{
	*size = this->_videoIn.buf.bytesused + DHT_SIZE);
	return (this->_videoIn.tmpBuffer);
}