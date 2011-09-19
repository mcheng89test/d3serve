#include "channelinvitationservice.h"
#include "../../proto/service/channel_invitation/definition/channel_invitation.pb.h"

ChannelInvitationService::ChannelInvitationService():
CoreService("ChannelInvitationService", 0x3, 0x83040608) {}

Packet ChannelInvitationService::Subscribe(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:ChannelInvitation:Subscribe()");
    bnet::protocol::channel_invitation::SubscribeResponse response;
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}  

Packet ChannelInvitationService::CallMethod(ClientService *client, Packet packetIn) {
    switch (packetIn.MethodId) {
        case 1: return Subscribe(client, packetIn);
        default: return Packet::getInvalidPacket();  
    }
}