#include "Processing/ImgProcessing.hpp"

#include <iostream>

ImgProcessing::ImgProcessing(processingType type) {
    this->_isGpuAccelerated = false;
    this->_type = type;
}

bool ImgProcessing::isGpuAccelerated() {
    return this->_isGpuAccelerated;
}

bool ImgProcessing::setGpuAccelerated() {
    if (cv::cuda::getCudaEnabledDeviceCount() == 0)
        this->_isGpuAccelerated = false;
    else
        this->_isGpuAccelerated = true;

    std::cout << "GPU ACCELERATED : " << this->_isGpuAccelerated << std::endl;

    return (this->_isGpuAccelerated);
}

void ImgProcessing::apply(cv::Mat & image) {
    if (!this->_isGpuAccelerated)
        this->applyCpu(image);
    else
        this->applyGpu(image);
}