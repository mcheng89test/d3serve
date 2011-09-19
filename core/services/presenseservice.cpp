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