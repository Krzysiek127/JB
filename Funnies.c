#include "Funnies.h"

WINBOOL changeWallpaper(const wchar_t *path)
{
    return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE);
}

void execCommand(JBCMD cmd)
{
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
        PlaySound("shambo.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case JB_SCREAM:
        // path up to change
        PlaySound("stalker.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;

    /* --- Wallpaper --- */
    case JB_SETWALL:
        changeWallpaper(cmd.args);
        break;
    case JB_SAVEWALL:
        wallpaper = cmd.args;
        break;
    case JB_LOADWALL:
        if (!wallpaper)
            sendError("No saved wallpaper");
        
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
    case JB_POPUP:
        char *msg = strtok(cmd.args, " ");
        char *wTitle = strtok(NULL, " ");
        
        MessageBoxW(NULL, msg, wTitle, 0);
        break;
    case JB_CMD:

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