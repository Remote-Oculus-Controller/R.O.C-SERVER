#include "Processing/ImgProcessingWrapper.hpp"

ImgProcessingWrapper::ImgProcessingWrapper() {
    this->_semaphore = new Semaphore(configuration::camera_count);
}

ImgProcessingWrapper::~ImgProcessingWrapper() {

}

void ImgProcessingWrapper::apply(cv::Mat & frame) {
    this->_semaphore->wait();
    for(std::vector<ImgProcessing *>::iterator it = this->_imgProcessings.begin(); it != this->_imgProcessings.end(); ++it) {
        (*it)->apply(frame);
    }
    this->_semaphore->notify();
}

unsigned int ImgProcessingWrapper::getProcessingCount() {
    return this->_imgProcessings.size();
}

bool ImgProcessingWrapper::addProcessing(ImgProcessing * toAdd , unsigned int index) {
    this->lockProcessings();
    this->_imgProcessings.insert(this->_imgProcessings.begin() + index , toAdd);
    this->unlockProcessings();
}

bool ImgProcessingWrapper::removeProcessing(unsigned int index) {
    this->lockProcessings();
    this->_imgProcessings.erase(this->_imgProcessings.begin() + index);
    this->unlockProcessings();
}

bool ImgProcessingWrapper::clearProcessing() {
    this->lockProcessings();
    this->_imgProcessings.erase(this->_imgProcessings.begin() , this->_imgProcessings.end());
    this->unlockProcessings();
}
void ImgProcessingWrapper::lockProcessings()

{
    this->_semaphore->wait(true);
}

void ImgProcessingWrapper::unlockProcessings() {
    this->_semaphore->notify(true);
}
