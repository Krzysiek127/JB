

#include "../Main.h"
#include "../src/Funnies.h"


/*
Broadcast funny commands over the whole internet
Epic trollage!!!1!
*/

// Used for debugging purposes, copied from stackoverflow
void hexDump (
    const char * desc,
    const void * addr,
    const int len,
    int perLine
) {
    // Silently ignore silly per-line values.

    if (perLine < 4 || perLine > 64) perLine = 16;

    int i;
    unsigned char buff[perLine+1];
    const unsigned char * pc = (const unsigned char *)addr;

    // Output description if given.

    if (desc != NULL) printf ("%s:\n", desc);

    // Length checks.

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < len; i++) {
        // Multiple of perLine means new or first line (with line offset).

        if ((i % perLine) == 0) {
            // Only print previous-line ASCII buffer for lines beyond first.

            if (i != 0) printf ("  %s\n", buff);

            // Output the offset of current line.

            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.

        printf (" %02x", pc[i]);

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % perLine] = '.';
        else
            buff[i % perLine] = pc[i];
        buff[(i % perLine) + 1] = '\0';
    }

    // Pad out last line if not exactly perLine characters.

    while ((i % perLine) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII buffer.

    printf ("  %s\n", buff);
}


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

    struct sockaddr_in recv_addr;
    //int len = sizeof(struct sockaddr_in);

    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = INADDR_BROADCAST;


    JBCMD payload;
    memset(&payload, '\x00', sizeof(payload));      // I've actually doxxed myself by broadcasting some path info laying in that memory
    // Remember to initialize your space!

    memcpy(payload.auth, argv[1], strlen(argv[1])); // AUTH_SIZE copies garbage, use strlen()
    payload.cmd = atoi(argv[2]);

    // name.exe auth id '<SEP>'.join()

    int TerminatedLength = 0;
    for (int i = 3; i < argc; i++) {
        TerminatedLength += strlen(argv[i]) + 1;  // If we add one to every strlen() then we can allocate enough memory for every separator
    }

    char *separgs = calloc(TerminatedLength, 1);
    assert(separgs);

    int argputPtr = 0;

    /* I think I've done it correctly, i hope there won't be an off-by-one error */

    for (int i = 3; i < argc; i++) {
        int len = strlen(argv[i]);
        memcpy(separgs + argputPtr, argv[i], len);
        argputPtr += len;

        separgs[argputPtr++] = SEPC;
    }


    /* 
        Even if separgs is longer than payload max size, we trim it.
        In later versions, we should include the length in JBCMD struct; we could send the args as long as we want.

        I'll look into it later
    */
    memcpy(payload.args, separgs, argputPtr);   // argputPtr should contain the byte length of all arguments

    int s = sendto(mSock, (const char *)&payload, sizeof(JBCMD), 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
    printf("Auth: \"%s\" (%lld/%lld)\nCMD: %u\n", payload.auth, strlen(payload.auth), sizeof(payload.auth), payload.cmd);
    hexDump("DATA", &payload, sizeof(payload), 16);
    printf("Argument length: %d\nBytes on wire: %d", argputPtr, s);

    // Remember kids to free your pointers after work!
    free(separgs);
}
