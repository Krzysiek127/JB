#include "Link.h"

LPSTR desktopPath()
{
    static char path[MAX_PATH];
    
    if(!SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))
        return path;

    return BADPATH;
}


HRESULT CreateLinks(int n) 
{
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
    psl->lpVtbl->SetIconLocation(psl, "Jail.ico", 0);
    psl->lpVtbl->SetDescription(psl, "You've been Jailed");
    psl->lpVtbl->SetPath(psl, "Jail.png");

    // Query IShellLink for the IPersistFile interface, used for saving the 
    // shortcut in persistent storage. 
    hres = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf); 

    char *path = desktopPath();
    if (hres < 0 || path == BADPATH) 
    {
        ppf->lpVtbl->Release(ppf);
        psl->lpVtbl->Release(psl); 
        JBlogErr("QueryInterface error");
        return -2;
    }

    strcat(path, "\\Jail");
    
    char tmpP[MAX_PATH];
    wchar_t wPath[MAX_PATH]; 
    char index[8];  // int(math.log10(X))+1


    /* ------ Creating links ------*/
    for (size_t i = 0; i < n; i++)
    {
        strcpy(tmpP, path);
        sprintf(index, "%lli", i);

        strcat(tmpP, index);

        // Ensure that the string is Unicode. 
        MultiByteToWideChar(CP_ACP, 0, tmpP, -1, wPath, MAX_PATH); 

        // Save the link
        hres = ppf->lpVtbl->Save(ppf, wPath, TRUE); 
    }

    JailNum = n;
    
    // Cleanup
    ppf->lpVtbl->Release(ppf);
    psl->lpVtbl->Release(psl); 
    CoUninitialize();

    return hres; 
}

HRESULT RemoveLinks()
{
    if(!JailNum)
        return 0;

    char *path = desktopPath();
    strcat(path, "//Jail");

    char tmpP[MAX_PATH];
    char index[8];

    for (size_t i = 0; i < JailNum; i++)
    {
        strcpy(tmpP, path);
        sprintf(index, "%li", i);

        strcat(tmpP, index);
        strcat(tmpP, ".lnk");

        remove(tmpP);
    }

    JailNum = 0;
}