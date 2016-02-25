#include "Processing/FaceDetect.hpp"

FaceDetect::FaceDetect(double treshold1, double treshold2, int matrixNm) : ImgProcessing(processingType::CANNY) {
    this->_treshold1 = treshold1;
    this->_treshold2 = treshold2;
    this->_matrixNum = matrixNm;
    std::string cascadeName = "assets/cascades/haarcascades/haarcascade_frontalface_alt.xml";
    if (!this->_cascade.load(cascadeName)) {
        //TODO log this error
        this->_cascadeIsLoaded = false;
    } else {
        this->_cascadeIsLoaded = true;
    }
}

FaceDetect::~FaceDetect() {

}

void FaceDetect::applyCpu(cv::Mat &image) {
    if (this->_cascadeIsLoaded)
        detectAndDraw(image, 1);
}


void FaceDetect::detectAndDraw(cv::Mat &img, double scale) {
    double t = 0;
    std::vector<cv::Rect> faces, faces2;
    const static cv::Scalar colors[] =
            {
                    cv::Scalar(255, 0, 0),
                    cv::Scalar(255, 128, 0),
                    cv::Scalar(255, 255, 0),
                    cv::Scalar(0, 255, 0),
                    cv::Scalar(0, 128, 255),
                    cv::Scalar(0, 255, 255),
                    cv::Scalar(0, 0, 255),
                    cv::Scalar(255, 0, 255)
            };
    cv::Mat gray, smallImg;

    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    double fx = 1 / scale;
    resize(gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR);
    equalizeHist(smallImg, smallImg);

    t = (double) cvGetTickCount();
    this->_cascade.detectMultiScale(smallImg, faces,
                                    1.1, 2, 0
                                            //|cv::CASCADE_FIND_BIGGEST_OBJECT
                                            //|cv::CASCADE_DO_ROUGH_SEARCH
                                            | cv::CASCADE_SCALE_IMAGE,
                                    cv::Size(30, 30));

    t = (double) cvGetTickCount() - t;
//    printf("detection time = %g ms\n", t / ((double) cvGetTickFrequency() * 1000.));
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Rect r = faces[i];
        cv::Mat smallImgROI;
        std::vector<cv::Rect> nestedObjects;
        cv::Point center;
        cv::Scalar color = colors[i % 8];
        int radius;

        double aspect_ratio = (double) r.width / r.height;
        if (0.75 < aspect_ratio && aspect_ratio < 1.3) {
            center.x = cvRound((r.x + r.width * 0.5) * scale);
            center.y = cvRound((r.y + r.height * 0.5) * scale);
            radius = cvRound((r.width + r.height) * 0.25 * scale);
            cv::circle(img, center, radius, color, 3, 8, 0);
        }
        else
            cv::rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)),
                          cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                          color, 3, 8, 0);

    }
}

void FaceDetect::applyGpu(cv::Mat &image) {
    this->applyCpu(image);
}


processingType FaceDetect::getID() {
    return (processingType::FACEDETECT);
}

void FaceDetect::displayType() {
    std::cout << "FACE_DETECT" << std::endl;
}