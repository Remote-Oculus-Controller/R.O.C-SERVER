#ifndef NETWORKINTERFACE_HPP
#define NETWORKINTERFACE_HPP

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "proto.pb.h"

class NetworkInterface {
public:

  static protocol::Packet * get(char * buffer , size_t size);
  static bool put(protocol::Packet * elem , char * buffer);

};

#endif // NETWORKINTERFACE_HPP
