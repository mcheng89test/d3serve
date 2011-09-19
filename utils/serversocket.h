#ifndef D3Serve_socket_h
#define D3Serve_socket_h

#include "clientsocket.h"

class ServerSocket {
public:
    ServerSocket();
    ClientSocket Accept();
    int Listen(int port);
    bool isListening();
    void Close();
private:
    int SocketFD;
};

#endif
