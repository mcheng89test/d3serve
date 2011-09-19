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