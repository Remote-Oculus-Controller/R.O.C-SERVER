#ifndef X265ENCODER_HPP
#define X265ENCODER_HPP

#include <iostream>
#include <stdint.h>
#include <queue>

#include "opencv2/opencv.hpp"

extern "C" 
{
	#include "libswscale/swscale.h"
    #include "libavutil/avutil.h"
    #include "libavutil/pixfmt.h"
    #include "x265_config.h"
    #include "x265.h"
}


class x265Encoder
{
public:
    x265Encoder(int width, int height , int fps);
    ~x265Encoder(void);

public:
    void initialize();
    void unInitialize();
    void encodeFrame(cv::Mat& image);
    bool isNalsAvailableInOutputQueue();
    x265_nal getNalUnit();

private:

	SwsContext * convertContext;
    // Use this context to convert your BGR Image to YUV image since x264 do not support RGB input
    std::queue<x265_nal> outputQueue;
    x265_param parameters;
    x265_picture picture_in,picture_out;
    x265_encoder* encoder;

    int _width;
    int _height;
    int _fps;
};

#endif // X265ENCODER_HPP
