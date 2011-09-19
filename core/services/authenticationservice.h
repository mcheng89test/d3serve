#ifndef D3Serve_authenticationservice_h
#define D3Serve_authenticationservice_h

#include "../service.h"

class AuthenticationService: public CoreService {
public:
    AuthenticationService();
    Packet CallMethod(ClientService *client, Packet packetIn);
private:
    Packet Logon(ClientService *client, Packet packetIn);
};

#endif
