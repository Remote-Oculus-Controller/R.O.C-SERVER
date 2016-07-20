#include <iostream>
#include "Network/NetworkInterface.hpp"
#include <bitset>

using namespace google::protobuf::io;

protocol::Packet * NetworkInterface::get(char * buffer , size_t size)
{
  protocol::Packet * elem = new protocol::Packet();
  ArrayInputStream ais(buffer,size);
  CodedInputStream coded_input(&ais);
  CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
  if (elem->ParseFromCodedStream(&coded_input))
  {
     coded_input.PopLimit(msgLimit);
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
