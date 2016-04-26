#ifndef X264ENCODER_HPP
#define X264ENCODER_HPP

#ifdef __cplusplus
#define __STDINT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#include <iostream>
//#include <concurrent_queue.h>
#include "opencv2/opencv.hpp"
#include <queue>
#include <stdint.h>

extern "C" 
{
    #include "x264_config.h"
    #include "x264.h"
    #include "libswscale/swscale.h"
    #include "libavutil/avutil.h"
    #include "libavutil/pixfmt.h"
}


class x264Encoder
{
public:
    x264Encoder(int width, int height , int fps);
    ~x264Encoder(void);

public:
    bool initilize();
    void unInitilize();
    void encodeFrame(cv::Mat& image);
    bool isNalsAvailableInOutputQueue();
    x264_nal_t getNalUnit();
private:
    // Use this context to convert your BGR Image to YUV image since x264 do not support RGB input
    SwsContext* convertContext;
    std::queue<x264_nal_t> outputQueue;
    x264_param_t parameters;
    x264_picture_t picture_in,picture_out;
    x264_t* encoder;

    int _width;
    int _height;
    int _fps;
};

#endif // X264ENCODER_HPP
