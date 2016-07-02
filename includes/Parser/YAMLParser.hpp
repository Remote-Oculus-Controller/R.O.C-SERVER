#ifndef YAML_PARSER_HPP
#define YAML_PARSER_HPP

#include "opencv2/opencv.hpp"
#include <vector>
#include <time.h>

class YAMLParser {
  public:

    YAMLParser(std::string fileName , cv::FileStorage::Mode mode);
    ~YAMLParser();

    bool isOpened();

    int 							getValueOf(std::string property);
    std::vector<int> 	getVectorOf(std::string property);

  private:

    std::string _filename;
    cv::FileStorage::Mode _mode;
    cv::FileStorage _file;

};

#endif // YAML_PARSER_HPP
