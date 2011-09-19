#include "toonexternalservice.h"
#include "../../proto/OnlineService.pb.h"
#include "../../proto/service/toon/toon_external.pb.h"

ToonExternalService::ToonExternalService():
CoreService("ToonExternalService", 0x2, 0x4124c31b) {}

Packet ToonExternalService::ToonList(ClientService *client, Packet packetIn)
{            
    Logger::Trace("RPC:ToonExternal:ToonList() - HAS COMMENTS");
    bnet::protocol::toon::external::ToonListResponse response;
    for (int i=0; i<client->Toons.size(); i++) {
        //response.add_toons();
        //response.mutable_toons(i)->
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