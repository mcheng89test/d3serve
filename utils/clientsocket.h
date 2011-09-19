#ifndef D3Serve_clientsocket_h
#define D3Serve_clientsocket_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class ClientSocket {
public:
    ClientSocket(int ConnectFD);
    bool isConnected();
    long Send(unsigned char *buffer, int len);
    long Receive(unsigned char *buffer, int len);
    void Close();
private:
    int ConnectFD;
};

#endif
