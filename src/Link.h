#ifndef LINK
#define LINK

// use libs needed for shell links
//#pragma comment(lib, "ole32.lib")
//#pragma comment(lib, "uuid.lib")

#include "../Main.h"

LPSTR desktopPath(); // fucking guess

HRESULT CreateLinks(int n); // create n desktop links
HRESULT RemoveLinks();      // remove previous links

#endif