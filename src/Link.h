#ifndef LINK
#define LINK

// use libs needed for shell links
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

#include "../Main.h"

extern short JailNum;

LPSTR desktopPath(); // fucking guess
HRESULT CreateLinks(LPCSTR pathSrc, int n); // create n links to pathSrc file
HRESULT ResolveLinks(); // delete made before links

#endif