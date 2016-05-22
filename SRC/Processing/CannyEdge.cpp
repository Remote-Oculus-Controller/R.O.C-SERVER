#include "Processing/CannyEdge.hpp"

CannyEdge::CannyEdge(double treshold1 , double treshold2 , int matrixNm) : ImgProcessing(processingType::CANNY)
{
	this->_treshold1 = treshold1;
	this->_treshold2 = treshold2;
	this->_matrixNum = matrixNm;
}

CannyEdge::~CannyEdge()
{

}

void CannyEdge::applyCpu(cv::Mat & image)
{
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::Canny(image, image, this->_treshold1,
    	this->_treshold2, this->_matrixNum);
    cvtColor(image, image, CV_GRAY2BGR);
}

void CannyEdge::applyGpu(cv::Mat & image)
{

}


processingType CannyEdge::getID()
{
	return (processingType::CANNY);
}

void CannyEdge::displayType()
{
	std::cout << "CANNY" << std::endl;
}
