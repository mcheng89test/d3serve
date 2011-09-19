#ifndef D3Serve_channelinvitationservice_h
#define D3Serve_channelinvitationservice_h

#include "../service.h"

class ChannelInvitationService: public CoreService {
public:
    ChannelInvitationService();
    Packet CallMethod(ClientService *client, Packet packetIn);
private:
    Packet Subscribe(ClientService *client, Packet packetIn);
};

#endif
