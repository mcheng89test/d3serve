#include "service.h"

std::map<byte, CoreService*> Service::ServiceMapping;
std::map<uint32, byte> Service::ServiceHashToIdMapping;

Packet Service::CallService(ClientService *client, Packet packetIn) {
    CoreService *cs = getServiceName(packetIn.ServiceId);
    if (cs == NULL)
        return Packet::getInvalidPacket();
    return cs->CallMethod(client, packetIn);
}

CoreService *Service::getServiceName(byte ServiceId) {
    std::map<byte, CoreService*>::iterator it = ServiceMapping.find(ServiceId);
    if (it == ServiceMapping.end())
        return NULL;
    return it->second;
}

byte Service::ServiceHashToId(uint32 ServiceHash) {
    std::map<uint32, byte>::iterator it = ServiceHashToIdMapping.find(ServiceHash);
    if (it == ServiceHashToIdMapping.end())
        return 0;
    return it->second;
}

CoreService::CoreService(std::string ClassName, byte ServiceId, uint32 ServiceHash) {
    this->ClassName = ClassName;
    this->ServiceId = ServiceId;
    this->ServiceHash = ServiceHash;
}

const char* CoreService::getClassName() {
    return ClassName.c_str();
}
byte CoreService::getServiceId() {
    return ServiceId;
}
uint32 CoreService::getServiceHash() {
    return ServiceHash;
}

ClientService::ClientService(ClientSocket *socket) {
    this->socket = socket;
}



#define MAP_SERVICE(CLASS_NAME) \
    c = new CLASS_NAME();\
    Service::ServiceMapping[c->getServiceId()] = c;\
    Service::ServiceHashToIdMapping[c->getServiceHash()] = c->getServiceId();

#include "services/baseservice.h"
#include "services/authenticationservice.h"
#include "services/channelinvitationservice.h"
#include "services/presenseservice.h"

void Service::Init() {
    CoreService *c;
    MAP_SERVICE(BaseService)
    MAP_SERVICE(AuthenticationService)
    MAP_SERVICE(ChannelInvitationService)
    MAP_SERVICE(PresenseService)
}