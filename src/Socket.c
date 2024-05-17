#include "Socket.h"
#include <stdio.h>

// i aint commenting this shit

int SockBegin(struct TeltharSocket *tsock) {
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

int SockRecv(struct TeltharSocket *tsock, void *out, size_t maxlen) {
    memset(out, '\0', maxlen);

    int recvl;
    if ((recvl = recvfrom(tsock->sock, out, maxlen, 0, (struct sockaddr*)&tsock->si_other, &tsock->si_otherlen)) == SOCKET_ERROR) {
        char err[32];
        sprintf(err, "WSA error: %d", WSAGetLastError());
        JBlogErr(err);
        return -1;
    }
    assert(recvl <= maxlen);
    return recvl;
}

int SockRespond(struct TeltharSocket *tsock, void *out, size_t len) {
    return recvfrom(tsock->sock, out, len, 0, (struct sockaddr*)&tsock->si_other, &tsock->si_otherlen);
}

void SockClose(struct TeltharSocket *tsock) {
    closesocket(tsock->sock);
    WSACleanup();
}