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