#ifndef SOCKET_HEADER
#define SOCKET_HEADER

#include "../Main.h"

struct TeltharSocket {
    SOCKET sock;
    struct sockaddr_in server, si_other;
    int si_otherlen;
    WSADATA wsa;
};

int UDPBegin(struct TeltharSocket *tsock);
int UDPRecv(struct TeltharSocket *tsock, void *out, size_t maxlen);
void UDPClose(struct TeltharSocket *tsock);
#endif