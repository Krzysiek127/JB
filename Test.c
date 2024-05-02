/*
Telthar's code to check his UDP wrapper
*/

#include <stdio.h>
#include "Socket.h"

struct TeltharSocket tsocket;
char buffer[512];

int main() {
    UDPBegin(&tsocket);
    while (1) {
        int r = UDPRecv(&tsocket, buffer, 512);
        if (r == -1)
            break;
        
        printf("%s", buffer);
    }
    UDPClose(&tsocket);
}