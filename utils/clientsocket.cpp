#include "clientsocket.h"
#include <errno.h>
#include "stdio.h"

ClientSocket::ClientSocket(int ConnectFD) {
    this->ConnectFD = ConnectFD;
}

bool ClientSocket::isConnected() {
    return ConnectFD != -1;
}

long ClientSocket::Send(unsigned char *buffer, int len) {
    long ret = send(ConnectFD, buffer, len, 0);
    //printf("length: %d error: %i\n", (int)ret, errno);
    return ret;
}

long ClientSocket::Receive(unsigned char *buffer, int len) {
    long ret = recv(ConnectFD, buffer, len, MSG_WAITALL);//returns byte count
    //printf("length: %d error: %i\n", (int)ret, errno);
    return ret;
}

void ClientSocket::Close() {
    if (ConnectFD != -1)
        close(ConnectFD);
    ConnectFD = -1;
}