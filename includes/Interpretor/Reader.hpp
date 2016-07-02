#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

class Reader {
  public:

    Reader();
    ~Reader();

    // SPLIT A STRING IN A VECTOR OF STRING

    std::vector<std::string> splitString();

    // COMBINE GETNEWLINE AND SPLITSTRING

    std::vector<std::string> getTokens();

    // FETCH NEW LINE FROM STDIN

    std::string getNewLine();

  private:

    std::string _input;
};


#endif // READER_HPP
