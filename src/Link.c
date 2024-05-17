#include "Link.h"

LPSTR desktopPath()
{
    static char path[MAX_PATH];
    
    if(!SHGetFolderPathA(HWND_BROADCAST, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))
        return path;

    return BADPATH;
}

static u_int JailNum = 0;

HRESULT CreateLinks(int n) 
{
    if (JailNum)
        RemoveLinks();

    IShellLink* psl; 
    CoInitialize(NULL);

    // Get a pointer to the IShellLink interface.
    HRESULT hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, (LPVOID*)&psl);

    if (hres < 0) 
    {
        psl->lpVtbl->Release(psl); 
        JBlogErr("CoCreateInstance error");
        return -1;
    }
    IPersistFile* ppf; 

    // Set the Shortcut parameters
    psl->lpVtbl->SetShowCmd(psl, SW_HIDE);
    char dir[MAX_PATH];
    getcwd(dir, MAX_PATH);
    strcat(dir, "\\res\\jail.ico");
    
    psl->lpVtbl->SetIconLocation(psl, dir, 0);
    psl->lpVtbl->SetDescription(psl, "You've been Jailed");
    psl->lpVtbl->SetPath(psl, "C:\\Windows\\Media\\onestop.mid");

    // Query IShellLink for the IPersistFile interface, used for saving the 
    // shortcut in persistent storage. 
    hres = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf); 

    char *path = desktopPath();
    if (hres < 0 || (!strcmp(path, BADPATH))) 
    {
        ppf->lpVtbl->Release(ppf);
        psl->lpVtbl->Release(psl); 
        JBlogErr("QueryInterface error");
        return -2;
    }

    strcat(path, "\\Jail");
    
    char tmpP[MAX_PATH];
    wchar_t wPath[MAX_PATH]; 

    /* ------ Creating links ------*/
    for (size_t i = 0; i < n; i++)
    {
        strcpy(tmpP, path);
        sprintf(tmpP, "%lli.lnk", i);

        // Ensure that the string is Unicode (conv to wchar)
        MultiByteToWideChar(CP_ACP, 0, tmpP, -1, wPath, MAX_PATH); 

        // Save the link
        ppf->lpVtbl->Save(ppf, wPath, TRUE); 
    }

    JailNum = n;
    
    // Cleanup
    ppf->lpVtbl->Release(ppf);
    psl->lpVtbl->Release(psl); 
    CoUninitialize();

    return hres; 
}

void RemoveLinks()
{
    if(!JailNum)
        return;

    char *path = desktopPath();
    if (!strcmp(path, BADPATH)) {
        JBlogErr("Bad desktop path");
        return;
    }

    strcat(path, "//Jail");

    char tmpP[MAX_PATH];

    /* ------ Removing links ------*/
    for (size_t i = 0; i < JailNum; i++)
    {
        strcpy(tmpP, path);
        sprintf(tmpP, "%lli.lnk", i);

        remove(tmpP);
    }

    JailNum = 0;
}