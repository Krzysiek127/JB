#ifndef HEADER
#define HEADER

#define _WIN32_WINIT_ 0x0A00

#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <shlobj.h>


#define PORT 2005
#define SEP "\x03"
#define SEPC '\x03'

#define CMD_ARGSZ 512
#define AUTH_LENGTH 24
#define BADPATH "**BADPATH**"

void log(const char *msg);
void logErr(const char *msg);

// pragma my nigga
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // TODO: Only works for MSVC. Make it work for GCC
#endif