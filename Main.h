#ifndef HEADER
#define HEADER

#pragma once

#define WIN32_LEAN_AND_MEAN // reduce the amount of slop
#define _WIN32_WINIT 0x0A00 // needed for windows slop
#define WINVER 0x0A00 // same dog different shit

//#include <winslop.h>
#include <winsock2.h>
#include <windows.h>

#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <shlobj.h>
#include <mbstring.h>
#include <mmsystem.h>
#include <shellapi.h>


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

#define VOLUME_UP 0xA0000   // volume 100
#define VOLUME_DOWN 0x90000 // volume 0

// logging to local text file
void JBlog(const char *msg);
void JBlogErr(const char *msg);

/*
void hexdump(
    const char *desc,
    const void *addr,
    const int len,
    int perLine
);
*/
#endif // HEADER