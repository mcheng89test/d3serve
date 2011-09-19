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

#include "presenseservice.h"
#include "../proto/lib/rpc/rpc.pb.h"

PresenseService::PresenseService():
CoreService("PresenseService", 0xb, 0xfa0796ff) {}

Packet PresenseService::Subscribe(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:PresenceService:Subscribe()");
    bnet::protocol::NoData response;            
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet PresenseService::Unsubscribe(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:PresenceService:Unsubscribe()");
    bnet::protocol::NoData response;            
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}


Packet PresenseService::Update(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:PresenceService:Update()");
    bnet::protocol::NoData response;            
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet PresenseService::Query(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:PresenceService:Query() Stub");
    // responds with NoData
    return Packet::getNullPacket();
}

Packet PresenseService::CallMethod(ClientService *client, Packet packetIn) {
    switch (packetIn.MethodId) {
        case 1: return Subscribe(client, packetIn);
        case 2: return Unsubscribe(client, packetIn);
        case 3: return Update(client, packetIn);
        case 4: return Query(client, packetIn);
        default: return Packet::getInvalidPacket();  
    }
}