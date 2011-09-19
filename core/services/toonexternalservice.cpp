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

#include "toonexternalservice.h"
#include "../../proto/OnlineService.pb.h"
#include "../../proto/service/toon/toon_external.pb.h"

ToonExternalService::ToonExternalService():
CoreService("ToonExternalService", 0x2, 0x4124c31b) {}

Packet ToonExternalService::ToonList(ClientService *client, Packet packetIn)
{            
    Logger::Trace("RPC:ToonExternal:ToonList() - HAS COMMENTS");
    bnet::protocol::toon::external::ToonListResponse response;
    for (int i=0; i<client->Account.Toons.size(); i++) {
        response.add_toons();
        response.mutable_toons(i)->set_high(::google::protobuf::uint64 value);
        response.mutable_toons(i)->set_low(::google::protobuf::uint64 value);
        //builder.AddToons(pair.Value.BnetEntityID);
    }
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet ToonExternalService::SelectToon(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:ToonExternal:SelectToon()");
    bnet::protocol::toon::external::SelectToonResponse response;
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet ToonExternalService::CreateToon(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:ToonExternal:CreateToon() - HAS COMMENTS");
    bnet::protocol::toon::external::CreateToonRequest request;
    request.ParseFromArray(packetIn.Payload, packetIn.PayloadLength);
    D3::OnlineService::HeroCreateParams heroCreateParams;
    heroCreateParams.ParsePartialFromString(request.attribute(0).value().message_value());
    
    bnet::protocol::toon::external::CreateToonResponse response;
    //var toon = new Toons.Toon(request.Name, (uint)heroCreateParams.GbidClass, heroCreateParams.IsFemale ? Toons.ToonGender.Female : Toons.ToonGender.Male, 1, client.Email);
    //if (Toons.ToonManager.SaveToon(toon)) builder.SetToon(toon.BnetEntityID);
    
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet ToonExternalService::DeleteToon(ClientService *client, Packet packetIn)
{
    Logger::Trace("RPC:ToonExternal:DeleteToon() - HAS COMMENTS");
    bnet::protocol::toon::external::DeleteToonRequest request;
    request.ParseFromArray(packetIn.Payload, packetIn.PayloadLength);
    
    uint64 id = request.toon().low();
    //var toon = Toons.ToonManager.GetToon(id);
    //Toons.ToonManager.DeleteToon(toon);
    
    bnet::protocol::toon::external::DeleteToonResponse response;
    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet ToonExternalService::CallMethod(ClientService *client, Packet packetIn) {
    switch (packetIn.MethodId) {
        case 1: return ToonList(client, packetIn);
        case 2: return SelectToon(client, packetIn);
        case 3: return CreateToon(client, packetIn);
        case 4: return DeleteToon(client, packetIn);
        default: return Packet::getInvalidPacket();  
    }
}