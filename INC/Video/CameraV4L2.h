#ifndef CAMERA_V4L2_H
#define CAMERA_V4L2_H

#include <linux/videodev.h>
#include "v4l2uvc.h"

#define   CAMERA_1 "/dev/video0"
#define   CAMERA_2 "/dev/video1"

class CameraV4L2
{
	public:
		
		CameraV4L2(char *device, int width, int height);
		~CameraV4L2();

		bool init();
		bool grabFrame();
		char * getFrame(size_t * size);

	private:


		char * _device;
		int  _format;
		int  _grabMethod;
		int  _width;
		int  _height;

		int _brightness;
		int _contrast;
		int _saturation;
		int _gain;

		struct vvdIn  _videoIn;


};
#endif // CAMERA_V4L2_H
