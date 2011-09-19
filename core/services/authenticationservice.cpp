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

#include "authenticationservice.h"
#include "../../proto/service/authentication/authentication.pb.h"

AuthenticationService::AuthenticationService():
    CoreService("AuthenticationService", 0x1, 0x0DECFC01) {}

Packet AuthenticationService::Logon(ClientService *client, Packet packetIn) {
    bnet::protocol::authentication::LogonRequest request;
    request.ParseFromArray(packetIn.Payload, packetIn.PayloadLength);
    
    Logger::Trace("RPC:Authentication:Logon(): %s", request.email().c_str());
    client->Account = AccountsManager::GetAccount(request.email());
    if (!client->Account.isInitialized())
        return Packet::getInvalidPacket();
        //invalid packet indicates error and will close connection
    
    bnet::protocol::authentication::LogonResponse response;
    response.mutable_account()->set_high(client->Account.getBnetAccountID().high());
    response.mutable_account()->set_low(client->Account.getBnetAccountID().low());
    response.mutable_game_account()->set_high(client->Account.getBnetGameAccountID().high());
    response.mutable_game_account()->set_low(client->Account.getBnetGameAccountID().low());
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}  

Packet AuthenticationService::CallMethod(ClientService *client, Packet packetIn) {
    switch (packetIn.MethodId) {
        case 1: return Logon(client, packetIn);
        default: return Packet::getInvalidPacket();  
    }
}