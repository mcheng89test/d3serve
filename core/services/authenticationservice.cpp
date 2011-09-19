#include "authenticationservice.h"
#include "../../proto/service/authentication/authentication.pb.h"

AuthenticationService::AuthenticationService():
    CoreService("AuthenticationService", 0x1, 0x0DECFC01) {}

Packet AuthenticationService::Logon(ClientService *client, Packet packetIn) {
    bnet::protocol::authentication::LogonRequest request;
    request.ParseFromArray(packetIn.Payload, packetIn.PayloadLength);
    
    Logger::Trace("RPC:Authentication:Logon(): %s", request.email().c_str());
    client->Account = AccountsManager::GetAccount(request.email());
    //std::transform(c->Email.begin(), c->Email.end(), c->Email.begin(), ::tolower);
    
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