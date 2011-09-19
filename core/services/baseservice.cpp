#include <vector>
#include "baseservice.h"
#include "../../proto/lib/rpc/connection.pb.h"


BaseService::BaseService():
    CoreService("BaseService", 0x0, 0x0) {}

Packet BaseService::Connect(ClientService *client, Packet packetIn) {
    Logger::Trace("RPC:BaseService:Connect()");
    time_t unix_time = time (NULL);
    bnet::protocol::connection::ConnectResponse response;
    response.mutable_server_id()->set_label(0xAAAA);
    response.mutable_server_id()->set_epoch((unsigned int)unix_time);
    response.mutable_client_id()->set_label(0xBBBB);
    response.mutable_client_id()->set_epoch((unsigned int)unix_time);
    return Packet(0xFE, 0x0, packetIn.RequestId, &response);
}

Packet BaseService::Bind(ClientService *client, Packet packetIn)
{
    static byte unknown_service = 100;
    Logger::Trace("RPC:BaseService:Bind()");
    bnet::protocol::connection::BindRequest request;
    request.ParseFromArray(packetIn.Payload, packetIn.PayloadLength);
    
    // supply service id's requested by client using service-hashes.
    std::vector<byte> requestedServiceIds;
    for (int i=0; i<request.imported_service_hash_size(); i++) {
        uint32 serviceHash = request.imported_service_hash(i);
        byte serviceId = Service::ServiceHashToId(serviceHash);
        CoreService *cs = (serviceId!=0?Service::getServiceName(serviceId):NULL);
        if (serviceId == 0) serviceId = unknown_service++;
        Logger::Trace("RPC:BaseService:Bind() - Hash: %u  ID: %u  Service: %s ", serviceHash, serviceId, (cs!=NULL?cs->getClassName():"N/A"));
        requestedServiceIds.push_back(serviceId);
    }
    
    // read services supplied by client..
    for (int i=0; i<request.exported_service_size(); i++) {
        bnet::protocol::connection::BoundService bs = request.exported_service(i);
        if (client->Services.find(bs.id()) != client->Services.end())
            client->Services[bs.id()] = bs.hash();
    }
    
    bnet::protocol::connection::BindResponse response;
    for (int i=0; i<requestedServiceIds.size(); i++)
        response.add_imported_service_id(requestedServiceIds.at(i));

    return Packet(0xfe, 0x0, packetIn.RequestId, &response);
}

Packet BaseService::CallMethod(ClientService *client, Packet packetIn) {
    switch (packetIn.MethodId) {
        case 1: return Connect(client, packetIn);
        case 2: return Bind(client, packetIn);
        default: return Packet::getInvalidPacket();  
    }
}