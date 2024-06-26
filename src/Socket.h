#ifndef SOCKET_HEADER
#define SOCKET_HEADER

#include "../Main.h"

// telthars socks
struct TeltharSocket {
    SOCKET sock;
    struct sockaddr_in server, si_other;
    int si_otherlen;
    WSADATA wsa;
};

int SockRespond(struct TeltharSocket *tsock, void *out, size_t len);
int SockBegin(struct TeltharSocket *tsock); // socket initialization
int SockRecv(struct TeltharSocket *tsock, void *out, size_t maxlen); //  recieving the out buffer
void SockClose(struct TeltharSocket *tsock); // closing socket connection

#endif