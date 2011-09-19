#ifndef D3Serve_packet_h
#define D3Serve_packet_h

typedef unsigned char byte;
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;

#include <string>
#include <google/protobuf/message.h>
#include "service.h"

class ClientService;

class Packet {
public:
    Packet();
    Packet(byte ServiceId, uint32 MethodId, uint16 RequestId, google::protobuf::Message *message);
    
    static Packet Read(ClientService client);
    int Write(ClientService client);
    
    static Packet getNullPacket();
    static Packet getInvalidPacket();
    
    bool isValid();
    std::string toString();

    byte ServiceId;
    uint32 MethodId;
    uint16 RequestId;
    uint64 Unknown;
    uint32 PayloadLength;
    byte *Payload;
    
private:
    bool valid;
    bool null;
};

#endif
