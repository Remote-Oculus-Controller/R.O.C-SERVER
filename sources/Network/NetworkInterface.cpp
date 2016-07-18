#include <iostream>
#include "Network/NetworkInterface.hpp"
#include <bitset>

using namespace google::protobuf::io;

protocol::Packet * NetworkInterface::get(char * buffer , size_t size)
{
  protocol::Packet * elem = new protocol::Packet();
  int bytecount;
  google::protobuf::io::ArrayInputStream ais(buffer,size);
  CodedInputStream coded_input(&ais);
  google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
  elem->ParseFromCodedStream(&coded_input);
  return elem;
}

bool NetworkInterface::put(protocol::Packet * elem , char * buffer)
{
    int size = elem->ByteSize();
    elem->SerializeToArray(buffer, size);
    std::cout << "Added message ! " << std::endl;
    return true;
}
