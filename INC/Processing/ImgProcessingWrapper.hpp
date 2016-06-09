#ifndef IMGPROCESSINGWRAPPER_HPP
#define IMGPROCESSINGWRAPPER_HPP

#include <vector>
#include <mutex>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

#include "Processing/ImgProcessing.hpp"
#include "Sync/Semaphore.hpp"
#include "Parser/ConfigParser.hpp"

class ImgProcessingWrapper
{
  public:

      ImgProcessingWrapper();
      ~ImgProcessingWrapper();

      void apply(cv::Mat & frame);

      unsigned int getProcessingCount();
      bool addProcessing(ImgProcessing * toAdd , unsigned int index);
      bool removeProcessing(unsigned int index);
      bool clearProcessing();

  private:

      void lockProcessings();
      void unlockProcessings();

      std::vector<ImgProcessing *>  _imgProcessings;
      std::mutex                    _lock;
      Semaphore *                   _semaphore;
};

#endif // IMGPROCESSINGWRAPPER_HPP
