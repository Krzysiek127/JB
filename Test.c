/*
Telthar's code to check his UDP wrapper
*/

#include <stdio.h>
#include "src\Socket.h"

struct TeltharSocket tsocket;
char buffer[16];

void JBlogErr(const char *msg) {
    printf("err: %s", msg);
}

int main() {
    UDPBegin(&tsocket);
    while (1) {
        int r = UDPRecv(&tsocket, buffer, 16);
        if (r == -1)
            break;
        
        printf("%s", buffer);
        //UDPRespond(&tsocket, "OK", 3);
    }
    UDPClose(&tsocket);
}