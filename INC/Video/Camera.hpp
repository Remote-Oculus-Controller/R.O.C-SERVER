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

#define  CONFIG_FILE ".config"

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
	bool upgradeQuality(int resolution, int compression);
	bool downgradeQuality(int resolution, int compression);
  	bool reOpenCamera();

	protected:

	//===================================================
	// FONCTIONS MASQUEES D'INITIALISATION
	//===================================================

	void initResolutions();


	//====================================================
	// ATTRIBUT PROPRE A LA CAMERA
	//====================================================

	int 						_id;
	int 						_resolutionIndex;

	std::vector<int>			_widthArray;
	std::vector<int>			_heightArray;

	cv::Mat 					_frame;
	
	cv::VideoCapture	*		_camera;

};

#endif // CAMERA_HPP
