#ifndef D3Serve_toonexternalservice_h
#define D3Serve_toonexternalservice_h

#include "../service.h"

class ToonExternalService: public CoreService {
public:
    ToonExternalService();
    Packet CallMethod(ClientService *client, Packet packetIn);
private:
    Packet ToonList(ClientService *client, Packet packetIn);
    Packet SelectToon(ClientService *client, Packet packetIn);
    Packet CreateToon(ClientService *client, Packet packetIn);
    Packet DeleteToon(ClientService *client, Packet packetIn);
};

#endif
