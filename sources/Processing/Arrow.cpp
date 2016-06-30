#include "Processing/Arrow.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Arrow::Arrow(int angle, int distance, int width, int height) : ImgProcessing(processingType::ARROW){
	this->_angle = angle;
	this->_distance = distance;
	this->_width = width;
	this->_height = height;
}

Arrow::~Arrow() {

}

void Arrow::applyCpu(cv::Mat &image) {
        this->Draw(image);
}

void Arrow::Draw(cv::Mat &image) {
	int size_x = this->_width * 15 / 100;
	int size_y = this->_height * 15 / 100;

	int thickness = 2;
	int lineType = 2;

	string str;
	ostringstream convert;
	convert << this->_distance;
	str = convert.str();
	
	double p1_x = this->_width/2 - (size_x / 4);
	double p1_y = this->_height/4;

	double p2_x = this->_width/2 + (size_x / 4);
	double p2_y = this->_height/4;

	double p3_x = this->_width/2 - (size_x / 4);
	double p3_y = this->_height/4 - (size_y / 1.5);

	double p4_x = this->_width/2 - (size_x / 2);
	double p4_y = this->_height/4 - (size_y / 1.5);

	double p5_x = this->_width/2 + (size_x / 4);
	double p5_y = this->_height/4 - (size_y / 1.5);

	double p6_x = this->_width/2 + (size_x / 2);
	double p6_y = this->_height/4 - (size_y / 1.5);

	double p7_x = this->_width/2;
	double p7_y = this->_height/4 - (size_y);

	Mat coordinates= (Mat_<double>(3,7) << p1_x, p2_x, p3_x, p4_x, p5_x, p6_x, p7_x,
											p1_y, p2_y, p3_y, p4_y, p5_y, p6_y, p7_y,
											1, 1, 1, 1, 1, 1, 1);

	Point2f pt(this->_width/2, this->_height/4 - 45);
	Mat r = getRotationMatrix2D(pt, this->_angle, 1);
	Mat result = r * coordinates;

	line(image, Point(result.at<double>(0,0), result.at<double>(1,0)), Point(result.at<double>(0,1), result.at<double>(1, 1)), Scalar(36, 255, 0), thickness, lineType); 
	
	line(image, Point(result.at<double>(0,0), result.at<double>(1,0)), Point(result.at<double>(0,2), result.at<double>(1,2)), Scalar(36, 255, 0), thickness, lineType);
	line(image, Point(result.at<double>(0,2), result.at<double>(1,2)), Point(result.at<double>(0,3), result.at<double>(1,3)), Scalar(36, 255, 0), thickness, lineType);
	
	line(image, Point(result.at<double>(0,1), result.at<double>(1,1)), Point(result.at<double>(0,4), result.at<double>(1,4)), Scalar(36, 255, 0), thickness, lineType);
	line(image, Point(result.at<double>(0,4), result.at<double>(1,4)), Point(result.at<double>(0,5), result.at<double>(1,5)), Scalar(36, 255, 0), thickness, lineType);

	line(image, Point(result.at<double>(0,3), result.at<double>(1,3)), Point(result.at<double>(0,6), result.at<double>(1,6)), Scalar(36, 255, 0), thickness, lineType);
	line(image, Point(result.at<double>(0,5), result.at<double>(1,5)), Point(result.at<double>(0,6), result.at<double>(1,6)), Scalar(36, 255, 0), thickness, lineType);

	putText(image, str, Point(this->_width/2 + size_x , this->_height/4 - (size_y / 2)), FONT_HERSHEY_PLAIN, 2, Scalar(36, 255, 0), thickness);
}

void Arrow::applyGpu(cv::Mat &image) {
    this->applyCpu(image);
}


processingType Arrow::getID() {
    return (processingType::ARROW);
}

void Arrow::displayType() {
    std::cout << "ARROW" << std::endl;
}