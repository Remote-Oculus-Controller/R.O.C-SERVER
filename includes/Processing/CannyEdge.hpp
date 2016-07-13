#ifndef CANNYEDGE_HPP
#define CANNYEDGE_HPP

#include "Processing/ImgProcessing.hpp"

class CannyEdge : public ImgProcessing
{
	public:

	CannyEdge(double treshold1 = 50 , double treshold2 = 150 , int matrixNum = 3);
	~CannyEdge();

	virtual processingType getID() const;
	virtual void displayType();

	private:

	virtual void applyCpu(cv::Mat & image);
	virtual void applyGpu(cv::Mat & image);

	double 	_treshold1;
	double 	_treshold2;
	int 	_matrixNum;

};

#endif // CANNYEDGE_HPP
