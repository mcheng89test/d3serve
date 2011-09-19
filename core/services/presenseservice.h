#ifndef D3Serve_presenseservice_h
#define D3Serve_presenseservice_h

#include "../service.h"

class PresenseService: public CoreService {
public:
    PresenseService();
    Packet CallMethod(ClientService *client, Packet packetIn);
private:
    Packet Subscribe(ClientService *client, Packet packetIn);
    Packet Unsubscribe(ClientService *client, Packet packetIn);
    Packet Update(ClientService *client, Packet packetIn);
    Packet Query(ClientService *client, Packet packetIn);
};

#endif
