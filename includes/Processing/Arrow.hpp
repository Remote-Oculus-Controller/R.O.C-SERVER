#ifndef ARROW_HPP
#define ARROW_HPP

#include "Processing/ImgProcessing.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class Arrow : public ImgProcessing {
  public:

    Arrow(int angle, int distance, int width, int height);

    ~Arrow();

    virtual processingType getID();

    virtual void displayType();

  private:

    void Draw(cv::Mat &img);

    virtual void applyCpu(cv::Mat &image);

    virtual void applyGpu(cv::Mat &image);


    int _angle;
    int _distance;
    int _height;
    int _width;
};

#endif // ARROW_HPP
