#ifndef LINK
#define LINK

// use libs needed for shell links
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

#include "../Main.h"

LPSTR desktopPath(); // fucking guess
void appendLinkId(char *c, int i); // append unique id from time and loop iterator
HRESULT CreateLinks(LPCSTR pathSrc, int n); // create n links to pathSrc file

#endif