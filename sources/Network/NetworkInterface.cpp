#include <iostream>
#include "Network/NetworkInterface.hpp"
#include <bitset>

using namespace google::protobuf::io;

protocol::Packet * NetworkInterface::get(char * buffer , size_t size)
{
  char * copy = new char[size];
  memcpy( copy , buffer , size);
  protocol::Packet * elem = new protocol::Packet();
  int bytecount;
  ArrayInputStream ais(buffer,size);
  CodedInputStream coded_input(&ais);
  CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
  if (elem->ParseFromCodedStream(&coded_input))
      return elem;
  return NULL;
}

bool NetworkInterface::put(protocol::Packet * elem , char * buffer)
{
    int size = elem->ByteSize();
    elem->SerializeToArray(buffer, size);
    return true;
}
