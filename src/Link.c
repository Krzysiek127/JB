#include "Link.h"

LPSTR desktopPath()
{
    static char path[MAX_PATH];
    
    if(!SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))
        return path;

    return "ERROR";
}

void appendLinkId(char *c, size_t i)
{
    char tmp[32];

    sprintf(tmp, "%li", time(NULL)); // time
    strcat(c, tmp);

    sprintf(tmp, "%u", i); // loop iter
    strcat(c, tmp);

    strcat(c, ".lnk"); // 
}

HRESULT CreateLinks(LPCSTR pathSrc, int n) 
{
    IShellLink* psl; 
    CoInitialize(NULL);

    // Get a pointer to the IShellLink interface.
    HRESULT hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, (LPVOID*)&psl);

    if (hres < 0) 
    { 
        JBlogErr("CoCreateInstance error");
        return -1;
    }
    IPersistFile* ppf; 

    // Set the Shortcut parameters
    psl->lpVtbl->SetShowCmd(psl, SW_HIDE);
    psl->lpVtbl->SetIconLocation(psl, "Jail.ico", 0);
    psl->lpVtbl->SetPath(psl, pathSrc);

    // Query IShellLink for the IPersistFile interface, used for saving the 
    // shortcut in persistent storage. 
    hres = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf); 

    if (hres < 0) 
    { 
        JBlogErr("QueryInterface error");
        return -2;
    }

    char *path = desktopPath();
    strcat(path, "\\Jail");
    
    char tmpP[MAX_PATH];
    wchar_t wsz[MAX_PATH]; 

    for (size_t i = 0; i < n; i++)
    {
        strcpy(tmpP, path);
        appendLinkId(tmpP, i);

        // Ensure that the string is Unicode. 
        MultiByteToWideChar(CP_ACP, 0, tmpP, -1, wsz, MAX_PATH); 

        // Save the link by calling IPersistFile::Save. 
        hres = ppf->lpVtbl->Save(ppf, wsz, TRUE); 
    }
    
    // Cleanup
    ppf->lpVtbl->Release(ppf);
    psl->lpVtbl->Release(psl); 
    CoUninitialize();

    return hres; 
}
