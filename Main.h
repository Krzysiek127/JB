#ifndef HEADER
#define HEADER

#pragma once

#define _WIN32_WINIT 0x0A00 // needed for windows shlop
#define WINVER 0xA00 // same dog different shit

//#include <winslop.h>
#include <winsock2.h>
#include <windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>
#include <tchar.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <shlobj.h>
#include <mbstring.h>


// Please for the love of god DO NOT UNCOMMENT THIS UNHOLY LINE
//#define TELTHAR_STUPID_WIDE_CHAR    LOCALE_ALL

/* ----- Defines ----- */
#define PORT 2005
#define SEP "\x03"   // argument separator
#define SEPC '\x03'  // char form
#define SEPL L"\x03" // wchar form

#define CMD_ARGSZ 512
#define AUTH_LENGTH 32 // powers of 2 nigga
#define BADPATH "**BADPATH**"

#ifdef APPCOMMAND_VOLUME_UP // weird compiler shenanigans
#undef APPCOMMAND_VOLUME_UP
#undef APPCOMMAND_VOLUME_DOWN
#endif

#define APPCOMMAND_VOLUME_UP 0xA0000    // volume 100
#define APPCOMMAND_VOLUME_DOWN 0x90000  // volume 0

// logging to local text file
void JBlog(const char *msg);
void JBlogErr(const char *msg);

void hexdump(
    const char *desc,
    const void *addr,
    const int len,
    int perLine
);
#endif // HEADER