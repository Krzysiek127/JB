#ifndef LINK
#define LINK

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

#include "../Main.h"

LPSTR desktopPath();
void appendLinkId(char *c, int i);
HRESULT CreateLinks(LPCSTR pathSrc, int n);

#endif