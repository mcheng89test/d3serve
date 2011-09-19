#ifndef D3Serve_service_h
#define D3Serve_service_h

#include <map>
#include "packet.h"
#include "database/accounts.h"
#include "database/toon.h"
#include "../utils/clientsocket.h"
#include "../utils/logger.h"

class Packet;

class ClientService {
public:
    ClientService(ClientSocket *socket);
    ClientSocket *socket;
    
    std::map<uint32, uint32> Services;
    Account Account;
    std::map<uint64, Toon> Toons;
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
