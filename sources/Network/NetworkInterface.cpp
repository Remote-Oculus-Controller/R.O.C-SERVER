#include "Network/NetworkInterface.hpp"

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
  google::protobuf::io::ArrayOutputStream aos(elem,size);
  CodedOutputStream *coded_output = new CodedOutputStream(&aos);
  elem->SerializeToCodedStream(coded_output);
  return true;
}
