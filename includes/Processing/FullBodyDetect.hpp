#ifndef FULLBODY_DETECT_HPP
#define FULLBODY_DETECT_HPP

#include "Processing/ImgProcessing.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class FullBodyDetect : public ImgProcessing {
public:

    FullBodyDetect(int scale = 1);
    ~FullBodyDetect();

    virtual processingType getID() const;
    virtual void displayType();

private:

    void detectAndDraw(cv::Mat &img);
    virtual void applyCpu(cv::Mat &image);
    virtual void applyGpu(cv::Mat &image);


    int _scale;
    cv::CascadeClassifier _cascade;

    #ifdef ROC_WITH_CUDA
    #endif

    bool _cascadeIsLoaded = false;
};

#endif // FULLBODY_DETECT_HPP
