

#include "../Main.h"
#include "../src/Funnies.h"


/*
Broadcast funny commands over the whole internet
Epic trollage!!!1!
*/


int main(int argc, char *argv[]) {
    // Usage:
    // Auth [Id. of command]

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Couldn't initialize Winsock.\n");
        return -1;
    }

    SOCKET mSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (mSock == INVALID_SOCKET) {
        printf("Invalid socket.\n");
        return -1;
    }

    char broadcast = '1';
    if (setsockopt(mSock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        printf("No broadcast capability.\n");
        closesocket(mSock);
        return -1;
    }

    struct sockaddr_in recv_addr, send_addr;
    int len = sizeof(struct sockaddr_in);

    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = INADDR_BROADCAST;


    JBCMD payload;
    memcpy(payload.auth, argv[1], 24);
    payload.cmd = atoi(argv[2]);

    // name.exe auth id '<SEP>'.join()

    int charWritten = 0;
    for (int i = 3; i < argc; i++) {
        if (charWritten >= CMD_ARGSZ)
            break;
        
        char *concat = strcat(payload.args, argv[i]);
        int concatlen = strlen(concat);

        memcpy(payload.args, concat, concatlen);
        charWritten += concatlen;
    }
}
