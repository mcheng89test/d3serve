#include <string>
#include "logger.h"
#include "serversocket.h"

ServerSocket::ServerSocket() {
    SocketFD = -1;
}

int ServerSocket::Listen(int port) {
    struct sockaddr_in stSockAddr;
    SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(-1 == SocketFD)
    {
        Logger::Error("Can not create socket");
        Close();
        return -1;
    }
    memset(&stSockAddr, 0, sizeof(stSockAddr));
    
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(port);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;
    
    if(-1 == bind(SocketFD,(struct sockaddr *)&stSockAddr, sizeof(stSockAddr)))
    {
        Logger::Error("Failed to bind to port %i", port);
        Close();
        return -2;
    }
    
    if(-1 == listen(SocketFD, 10))
    {
        Logger::Error("Could not listen on socket");
        Close();
        return -3;
    }
    return 0;
}

ClientSocket ServerSocket::Accept() {
    int ConnectFD = accept(SocketFD, NULL, NULL);
    if(0 > ConnectFD)
    {
        Logger::Error("Accept failed");
        Close();
        ConnectFD = -1;
    }
    ClientSocket c(ConnectFD);
    return c;
}

bool ServerSocket::isListening() {
    return SocketFD != -1;
}

void ServerSocket::Close() {
    if (SocketFD != -1)
        close(SocketFD);
    SocketFD = -1;
}