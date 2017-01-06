#include "Processing/RedCirclesDetect.hpp"

RedCirclesDetect::RedCirclesDetect(int minDist, int minRadius, int maxRadius) : ImgProcessing(
        processingType::REDCIRCLESDETECT) {
    this->_minDist = minDist;
    this->_minRadius = minRadius;
    this->_maxRadius = maxRadius;

}

RedCirclesDetect::~RedCirclesDetect() {

}

void RedCirclesDetect::applyCpu(cv::Mat &image) {
    detectAndDraw(image);
}


void RedCirclesDetect::detectAndDraw(cv::Mat &image) {

    // we have to modify the image only the apply the processing
    cv::Mat bgr_image = image.clone();

    // remove the noise
    cv::medianBlur(bgr_image, bgr_image, 3);

    // hsv image will allow us to remove every colors except the red
    cv::Mat hsv_image;
    cv::cvtColor(bgr_image, hsv_image, cv::COLOR_BGR2HSV);

    // in hsv we need range of color
    cv::Mat lower_red_hue_range;
    cv::Mat upper_red_hue_range;
    cv::inRange(hsv_image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lower_red_hue_range);
    cv::inRange(hsv_image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upper_red_hue_range);


    // we 'merge' the two matrix with the red in one 
    cv::Mat red_hue_image;
    cv::addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, red_hue_image);

    // reduce detail without that we would need almost perfect circles
    cv::GaussianBlur(red_hue_image, red_hue_image, cv::Size(9, 9), 2, 2);

    // detect the circle and fill the vector circles
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(red_hue_image, circles, CV_HOUGH_GRADIENT, 1, this->_minDist, 100, 40, this->_minRadius,
                     this->_maxRadius);
    
    // apply the circles to the images
    for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle) {
        cv::Point center((int) std::round(circles[current_circle][0]),
                         (int) std::round(circles[current_circle][1]));
        int radius = (int) std::round(circles[current_circle][2]);

        cv::circle(image, center, radius, cv::Scalar(0, 255, 0));
    }
}

void RedCirclesDetect::applyGpu(cv::Mat &image) {
    this->applyCpu(image);
}


processingType RedCirclesDetect::getID() {
    return (processingType::REDCIRCLESDETECT);
}

void RedCirclesDetect::displayType() {
    std::cout << "RED_CIRCLES_DETECT" << std::endl;
}