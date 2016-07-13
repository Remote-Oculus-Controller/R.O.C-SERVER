#ifndef FACE_DETECT_HPP
#define FACE_DETECT_HPP

#include "Processing/ImgProcessing.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class FaceDetect : public ImgProcessing {
public:

    FaceDetect(int scale = 1);
    ~FaceDetect();

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

#endif // FACE_DETECT_HPP
