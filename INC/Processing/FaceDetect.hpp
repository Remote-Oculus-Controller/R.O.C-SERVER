#ifndef FACE_DETECT_HPP
#define FACE_DETECT_HPP

#include "Processing/ImgProcessing.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class FaceDetect : public ImgProcessing {
public:

    FaceDetect(double treshold1 = 50, double treshold2 = 150, int matrixNum = 3);

    ~FaceDetect();

    virtual processingType getID();

    virtual void displayType();

private:

    void detectAndDraw(cv::Mat &img, double scale);

    virtual void applyCpu(cv::Mat &image);

    virtual void applyGpu(cv::Mat &image);



    double _treshold1;
    double _treshold2;
    int _matrixNum;
    cv::CascadeClassifier _cascade;
    bool _cascadeIsLoaded = false;
};

#endif // FACE_DETECT_HPP
