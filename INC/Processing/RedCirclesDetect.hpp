#ifndef RED_CIRCLES_DETECT_HPP
#define RED_CIRCLES_DETECT_HPP

#include "Processing/ImgProcessing.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>
#include <iostream>

class RedCirclesDetect : public ImgProcessing {
public:

    RedCirclesDetect(int minDist = 100, int minRadius = 0, int maxRadius = 0);

    ~RedCirclesDetect();

    virtual processingType getID();

    virtual void displayType();

private:

    void detectAndDraw(cv::Mat &img);

    virtual void applyCpu(cv::Mat &image);

    virtual void applyGpu(cv::Mat &image);


    int _minDist; //  Minimum distance between the centers of the detected circles.
    int _minRadius; // Minimum circle radius.
    int _maxRadius; // Maximum circle radius.
};

#endif // RED_CIRCLES_DETECT_HPP
