#include "Funnies.h"

WINBOOL changeWallpaper(const wchar_t *path)
{
    return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE);
}

void execCommand(JBCMD cmd) {
    switch (cmd.cmd) {
    case JB_SETWALL:
        // TODO
        changeWallpaper(cmd.args);
        break;
    }
}