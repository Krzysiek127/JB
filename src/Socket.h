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

int UDPRespond(struct TeltharSocket *tsock, void *out, size_t len);
int UDPBegin(struct TeltharSocket *tsock); // socket initialization
int UDPRecv(struct TeltharSocket *tsock, void *out, size_t maxlen); //  recieving the out buffer
void UDPClose(struct TeltharSocket *tsock); // closing socket connection

#endif