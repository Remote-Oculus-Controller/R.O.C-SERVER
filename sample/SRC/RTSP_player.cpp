#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

int main(int argc , char ** argv)
{
  if (argc < 2)
    return 1;
  
  cv::VideoCapture capture(argv[1]);
  if (!capture.isOpened())
    return 1;

  cv::namedWindow("RTSP Stream", CV_WINDOW_AUTOSIZE);
  cv::Mat frame;

  while(true)
  {
    if (!capture.read(frame))
      return 1;
    cv::imshow("TEST", frame);
    cv::waitKey(1);
  }
}
