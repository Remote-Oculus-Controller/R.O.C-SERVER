#include <iostream>
#include <ctime>
#include "Network/TcpServer.hpp"
#include "Network/UdpServer.hpp"
#include "Video/Camera.hpp"

int main(int argc, char**argv)
{
  std::vector<unsigned char> data;
  std::vector<UdpPacket> * packets;
  
  UdpServer server = UdpServer(1250);
  Camera    camera = Camera(0, 30);

  char a;

  if (camera.initCamera() == false)
    exit(0);
  if (server.initServer() == false)
    exit(0);
  
  server.runServer();

  std::cout << "Waiting client ping..." << std::endl;

  //  server.Read(&a, 1);

  cv::namedWindow("frame");

  std::cout << "Streaming..." << std::endl;

  while (1)
     {
       clock_t launch = clock();

      camera.captureNewFrame();
      camera.compressFrame();
      //server.bundleUpData(camera.getCompressedFrame(), 1);
      //packets = server.getBundledUpData();
      cv::imshow("frame", camera.getFrame());
      //for (int i = 0; i < packets->size() ; i++)
      // server.Send((char *) &((*packets)[i]), sizeof(UdpPacket));
      clock_t done = clock();

        std::cout << "Sending frame !" << std::endl;
      double diff = (double) (done - launch) / CLOCKS_PER_SEC;
      std::cout << "In : " << diff << " seconds" << std::endl;
      cv::waitKey(1);
      }
  
  return (0);
}
