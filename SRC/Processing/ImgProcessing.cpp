#include "Processing/ImgProcessing.hpp"

ImgProcessing::ImgProcessing()
{
	this->_isGpuAccelerated = false;
}

bool ImgProcessing::isGpuAccelerated()
{
	return this->_isGpuAccelerated;
}

bool ImgProcessing::setGpuAccelerated(bool value)
{
	// TODO
	//
	// AJOUTER CHECK DU SUPPORT CUDA
	// SI INEXISTANT , SETTER A FALSE
	// RENVOYER FALSE SI value VALAIT true

	this->_isGpuAccelerated = value;
	return (true);
}