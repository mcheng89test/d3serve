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

#ifndef D3Serve_service_h
#define D3Serve_service_h

#include <map>
#include "packet.h"
#include "database/accounts.h"
#include "../utils/clientsocket.h"
#include "../utils/logger.h"

class Packet;

class ClientService {
public:
    ClientService(ClientSocket *socket);
    ClientSocket *socket;
    
    std::map<uint32, uint32> Services;
    Account Account;
};

class CoreService {
public:
    CoreService(std::string ClassName, byte ServiceId, uint32 ServiceHash);
    const char* getClassName();
    byte getServiceId();
    uint32 getServiceHash();
    virtual Packet CallMethod(ClientService *client, Packet packetIn) = 0;
protected:
    std::string ClassName;
    byte ServiceId;
    uint32 ServiceHash;
};

class Service {
public:
    static void Init();
    static Packet CallService(ClientService *client, Packet packetIn);
    static CoreService* getServiceName(byte ServiceId);
    static byte ServiceHashToId(uint32 ServiceHash);
private:
    static std::map<byte, CoreService*> ServiceMapping;
    static std::map<uint32, byte> ServiceHashToIdMapping;
};

#endif
