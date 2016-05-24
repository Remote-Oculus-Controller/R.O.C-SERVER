#include "Parser/ConfigParser.hpp"

namespace configuration
{
  unsigned int camera_count = 0;
  unsigned int timeout = 0;
  unsigned int width = 0;
  unsigned int height = 0;
  unsigned int fps = 0;
  unsigned int port = 0;

  bool loadConfig()
  {
    logger::log(START_CONFIG , logger::logType::INFO);

    YAMLParser parser = YAMLParser(CONFIG_FILE , cv::FileStorage::READ);
    if (parser.isOpened() == false) {
      logger::log(ERROR_CONFIG_OPEN , logger::logType::FAILURE);
      return false;
    }

    camera_count = parser.getValueOf("camera_count");
    timeout = parser.getValueOf("timeout");
    width = parser.getValueOf("width");
    height = parser.getValueOf("height");
    fps = parser.getValueOf("fps");
    port = parser.getValueOf("port");

    if (ConfigParser::checkCamerasCount() == false)
    {
      logger::log(ERROR_CAMERAS_COUNT , logger::logType::FAILURE);
      return false;
    }
    if (ConfigParser::checkWidth() == false)
    {
      logger::log(ERROR_WIDTH , logger::logType::FAILURE);
      return false;

    }
    if (ConfigParser::checkHeight() == false)
    {

      logger::log(ERROR_HEIGHT , logger::logType::FAILURE);
      return false;

    }
    if (ConfigParser::checkFps() == false)
    {

      logger::log(ERROR_FPS , logger::logType::FAILURE);
      return false;

    }
    if (ConfigParser::checkTimeout() == false)
    {

      logger::log(ERROR_TIMEOUT , logger::logType::FAILURE);
      return false;

    }
    if (ConfigParser::checkPort() == false)
    {

      logger::log(ERROR_PORT , logger::logType::FAILURE);
      return false;

    }

    logger::log(SUCCESS_CONFIG , logger::logType::SUCCESS);
    ConfigParser::logConfig();
    return true;
  }

  bool ConfigParser::checkCamerasCount()
  {
    return camera_count > 0;
  }

  bool ConfigParser::checkWidth()
  {
    return width > 0;
  }

  bool ConfigParser::checkHeight()
  {
    return height > 0;
  }

  bool ConfigParser::checkFps()
  {
    return fps > 0;
  }

  bool ConfigParser::checkTimeout()
  {
    return timeout > (1000 / fps);
  }

  bool ConfigParser::checkPort()
  {
    return port > 0;
  }

  bool ConfigParser::logConfig()
  {
    logger::log(INFO_CONFIG("Devices" , camera_count), logger::logType::INFO);
    logger::log(INFO_CONFIG("Width" , width) , logger::logType::INFO);
    logger::log(INFO_CONFIG("Height" , height) , logger::logType::INFO);
    logger::log(INFO_CONFIG("Fps" , fps) , logger::logType::INFO);
    logger::log(INFO_CONFIG("Timeout" , timeout) , logger::logType::INFO);
    logger::log(INFO_CONFIG("Port" , port) , logger::logType::INFO);
  }
}
