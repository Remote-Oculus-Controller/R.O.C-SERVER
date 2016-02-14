#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

#include "Parser/YAMLParser.hpp"

#define  CAMERA_CONFIGURATION_FILE "config/resolutions.yml"

using namespace cv;

class Camera
{

	public:
	
	//====================================================
	// CONSTRUCTEUR / DESTRUCTEUR
	//====================================================

	Camera(int id = 0);
	~Camera();

	//====================================================
	// GETTERS
	//====================================================

	int getId() const;

	Mat & getFrame();
	std::vector<unsigned char> * getCompressedFrame();

	//====================================================
	// SETTERS
	//====================================================


	//====================================================
	// FONCTIONS GENERALES POUR LA CAMERA
	//====================================================

	bool initCamera();
	bool captureNewFrame();
  	bool reOpenCamera();

  	int getWidth();
  	int getHeight();
  	int getFps();

	protected:

	//===================================================
	// FONCTIONS MASQUEES D'INITIALISATION
	//===================================================

	void initResolutions();


	//====================================================
	// ATTRIBUT PROPRE A LA CAMERA
	//====================================================

	int 						_id;
	
	cv::Mat 					_frame;
	cv::VideoCapture	*		_camera;

	int 						_width;
	int 						_height;
	int 						_fps;

};

#endif // CAMERA_HPP
