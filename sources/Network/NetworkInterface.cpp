#include <iostream>
#include "Network/NetworkInterface.hpp"
#include <bitset>

using namespace google::protobuf::io;

protocol::Packet * NetworkInterface::get(char * buffer , size_t size)
{
  char * copy = new char[size];
  memcpy(copy , buffer , size);
  protocol::Packet * elem = new protocol::Packet();
  ArrayInputStream ais(copy ,size);
  CodedInputStream coded_input(&ais);
  CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
  if (elem->ParseFromCodedStream(&coded_input))
  {
     coded_input.PopLimit(msgLimit);
     std::cout << "MESSAGE RECEIVE ID : " << elem->id() << std::endl;
     return elem;
  }
  coded_input.PopLimit(msgLimit);
  return NULL;
}

bool NetworkInterface::put(protocol::Packet * elem , char * buffer)
{
    int size = elem->ByteSize();
    elem->SerializeToArray(buffer, size);
    return true;
}
