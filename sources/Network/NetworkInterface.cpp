#include <iostream>
#include "Network/NetworkInterface.hpp"
#include <bitset>

using namespace google::protobuf::io;

rocproto::Packet * NetworkInterface::get(char * buffer , size_t size)
{
  rocproto::Packet * elem = new rocproto::Packet();
  ArrayInputStream ais(buffer ,size);
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

bool NetworkInterface::put(rocproto::Packet * elem , char * buffer)
{
    int size = elem->ByteSize();
    elem->SerializeToArray(buffer, size);
    return true;
}
