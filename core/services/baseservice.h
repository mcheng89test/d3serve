#ifndef D3Serve_baseservice_h
#define D3Serve_baseservice_h

#include "../service.h"

class BaseService: public CoreService {
public:
    BaseService();
    Packet CallMethod(ClientService *client, Packet packetIn);
private:
    Packet Connect(ClientService *client, Packet packetIn);
    Packet Bind(ClientService *client, Packet packetIn);
};

#endif
