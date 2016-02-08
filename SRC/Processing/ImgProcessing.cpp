#include "Processing/ImgProcessing.hpp"

#include <iostream>

ImgProcessing::ImgProcessing(ImgProcessingParams * params)
{
	this->_isGpuAccelerated = false;
	this->_params = params;
}

bool ImgProcessing::isGpuAccelerated()
{
	return this->_isGpuAccelerated;
}

bool ImgProcessing::setGpuAccelerated()
{
	if (cv::cuda::getCudaEnabledDeviceCount() == 0)
	 	this->_isGpuAccelerated = false;
	else
		this->_isGpuAccelerated = true;

	std::cout << "GPU ACCELERATED : " << this->_isGpuAccelerated << std::endl;

	return (this->_isGpuAccelerated);
}