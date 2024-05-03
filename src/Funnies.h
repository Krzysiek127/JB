#ifndef FUN
#define FUN

#include "../Main.h"

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
    JB_CDEJECT,     // Eject disk drive
    JB_POPUPW,      // MessageBoxW
    JB_POPUPA,      // MessageBoxA
    JB_EXEC,        // execute a cmdlet
    JB_ROTATESCR,   // SetDisplayAutoRotationPreferences
    JB_CHANGERES,   

    JB_SENDKEY      // ?
} JB_Instruction;

typedef struct {
    char auth[AUTH_LENGTH];
    JB_Instruction cmd;     // JB_POPUP "Title¿"Polskie szamba liderem są w kraju"\0"
    char args[CMD_ARGSZ];
} JBCMD; // JailBreaker Command

//WINBOOL changeWallpaper(char *path);  // I think we don't need to expose it

void execCommand(JBCMD cmd);
void sendError(const char *message);

#endif