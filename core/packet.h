/*
 Diablo 3 Server Emulator
 Copyright (C) 2011 D3Sharp (https://github.com/raistlinthewiz/d3sharp)
 
 Ported to C++ by mcheng89
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
