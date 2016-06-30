#include "Encoder/x265Encoder.hpp"

x265Encoder::x265Encoder(int width, int height, int fps) 
{
	this->_width = width;
	this->_height = height;
	this->_fps = fps;
}

x265Encoder::~x265Encoder(void)
{

}


void x265Encoder::initialize()
{
	
}

void x265Encoder::unInitialize()
{
	x265_encoder_close(encoder);
	sws_freeContext(convertContext);
}

void x265Encoder::encodeFrame(cv::Mat & image)
{

}

bool x265Encoder::isNalsAvailableInOutputQueue()
{
	return (!outputQueue.empty());
}

x265_nal x265Encoder::getNalUnit()
{
	x265_nal nal;
	nal = outputQueue.front();
	outputQueue.pop();
	return nal;
}