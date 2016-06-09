#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include "Parser/YAMLParser.hpp"
#include "Logger/Logger.hpp"

#define CONFIG_FILE "config/resolutions.yml"

namespace configuration
{
  extern unsigned int camera_count;
  extern unsigned int timeout;
  extern unsigned int width;
  extern unsigned int height;
  extern unsigned int fps;
  extern unsigned int port;
  extern unsigned int tcpPort;
  extern std::vector<int> cameras_id;


  bool loadConfig();

  class ConfigParser
  {
  public:
    static bool checkCamerasCount();
    static bool checkWidth();
    static bool checkHeight();
    static bool checkFps();
    static bool checkIDs();
    static bool checkTimeout();
    static bool checkPort();
    static bool logConfig();
  };
}

#endif // CONFIGPARSER_HPP
