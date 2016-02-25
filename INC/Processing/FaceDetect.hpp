#ifndef FACE_DETECT_HPP
#define FACE_DETECT_HPP

#include "Processing/ImgProcessing.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class FaceDetect : public ImgProcessing {
public:

    FaceDetect(int scale = 1);

    ~FaceDetect();

    virtual processingType getID();

    virtual void displayType();

private:

    void detectAndDraw(cv::Mat &img);

    virtual void applyCpu(cv::Mat &image);

    virtual void applyGpu(cv::Mat &image);


    int _scale;
    cv::CascadeClassifier _cascade;
    bool _cascadeIsLoaded = false;
};

#endif // FACE_DETECT_HPP
