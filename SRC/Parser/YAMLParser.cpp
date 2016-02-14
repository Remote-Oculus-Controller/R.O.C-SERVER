#include "Parser/YAMLParser.hpp"

YAMLParser::YAMLParser(std::string filename , cv::FileStorage::Mode mode)
{
	this->_filename = filename;
	this->_mode = mode;

	this->_file = cv::FileStorage(this->_filename , this->_mode);
}

YAMLParser::~YAMLParser()
{
	this->_file.release();
}

int YAMLParser::getValueOf(std::string property)
{
	int value;

	this->_file[property] >> value;
	return (value);
}

bool YAMLParser::isOpened()
{
	return (this->_file.isOpened());
}