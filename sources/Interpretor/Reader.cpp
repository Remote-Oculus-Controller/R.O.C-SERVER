#include "Interpretor/Reader.hpp"

Reader::Reader() {

}

Reader::~Reader() {

}

std::string Reader::getNewLine() {
    std::string input;
    std::getline(std::cin , input);
    this->_input = input;

    return (input);
}

std::vector<std::string> Reader::splitString() {
    std::istringstream iss(this->_input);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>{}};

    return (tokens);
}

std::vector<std::string> Reader::getTokens() {
    this->getNewLine();
    return (this->splitString());
}