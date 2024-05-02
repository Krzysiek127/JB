#include "Socket.h"
#include <stdio.h>


int UDPBegin(struct TeltharSocket *tsock) {
    tsock->si_otherlen = sizeof(tsock->si_other);
    
    if (WSAStartup(MAKEWORD(2, 2), &tsock->wsa) != 0) {
        return -1;
    }

    if ((tsock->sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        return -2;
    }

    tsock->server.sin_family = AF_INET;
    tsock->server.sin_addr.s_addr = INADDR_ANY;
    tsock->server.sin_port = htons(PORT);

    if (bind(tsock->sock, (struct sockaddr*)&tsock->server, sizeof(tsock->server)) == SOCKET_ERROR) {
        return -3;
    }

    return 0;
}

//void UDPSend(void *data, size_t len) {
//    send()
//}

int UDPRecv(struct TeltharSocket *tsock, void *out, size_t maxlen) {
    memset(out, '\0', maxlen);

    int recvl;
    if ((recvl = recvfrom(tsock->sock, out, maxlen, 0, (struct sockaddr*)&tsock->si_other, &tsock->si_otherlen)) == SOCKET_ERROR) {
        printf("WSA error: %d", WSAGetLastError());
        return -1;
    }

    return recvl;
}

void UDPClose(struct TeltharSocket *tsock) {
    closesocket(tsock->sock);
    WSACleanup();
}