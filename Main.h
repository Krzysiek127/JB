#ifndef HEADER
#define HEADER

#pragma once

#define _WIN32_WINIT 0x0A00 // needed for windows shlop
#define WINVER 0xA00 // same dog different shit

//#include <winslop.h>
#include <winsock2.h>
#include <windows.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <shlobj.h>
#include <wchar.h>
#include <tchar.h>
#include <locale.h>
#include <mbstring.h>

// Please for the love of god DO NOT UNCOMMENT THIS UNHOLY LINE
//#define TELTHAR_STUPID_WIDE_CHAR    LOCALE_ALL

/* ----- Defines ----- */
#define PORT 2005
#define SEP "\x03"  // argument separator
#define SEPC '\x03' // char form
#define SEPL L"\x03" // wchar form

#define CMD_ARGSZ 512
#define AUTH_LENGTH 32 // powers of 2 nigga
#define BADPATH "**BADPATH**"

#ifdef APPCOMMAND_VOLUME_UP // weird compiler shenanigans
#undef APPCOMMAND_VOLUME_UP
#undef APPCOMMAND_VOLUME_DOWN
#endif

#define APPCOMMAND_VOLUME_UP 0xA0000 // volume 100
#define APPCOMMAND_VOLUME_DOWN 0x90000 // volume 0

// logging to local text file
void JBlog(const char *msg);
void JBlogErr(const char *msg);

// pragma my nigga
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // TODO: Only works for MSVC. Make it work for GCC
void hexDump (
    const char *desc,
    const void *addr,
    const int len,
    int perLine
);
#endif