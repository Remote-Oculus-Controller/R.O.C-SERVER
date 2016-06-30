#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

#include "Logger/Logger.hpp"
#include "Parser/ConfigParser.hpp"

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
	bool reOpenCamera();
	bool retrieveFrame();
	bool grabFrame();
	bool flipFrame();
	bool set(int propId , double value);
	bool setZoom(double value);

  int getWidth();
  int getHeight();
  int getFps();

	protected:

	bool doZoom();

	//===================================================
	// FONCTIONS MASQUEES D'INITIALISATION
	//===================================================

	bool    initResolutions();

	//====================================================
	// ATTRIBUT PROPRE A LA CAMERA
	//====================================================

	int 									_id;

	cv::Mat 							_frontFrame;
	cv::Mat 							_backFrame;
	cv::VideoCapture	*		_camera;

	int 									_width;
	int 									_height;
	int 									_fps;

	double 								_zoom;
	std::mutex 						_lock;

};

#endif // CAMERA_HPP
