#include "Link.h"

LPSTR desktopPath()
{
    static char path[MAX_PATH];
    
    if(!SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))
        return path;

    return "ERROR";
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
    psl->lpVtbl->SetDescription(psl, "You've been Jailed");
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
    wchar_t wPath[MAX_PATH]; 
    char index[8];  // int(math.log10(X))+1

    for (size_t i = 0; i < n; i++)
    {
        strcpy(tmpP, path);
        sprintf(index, "%lli", i);

        strcat(tmpP, index);

        // Ensure that the string is Unicode. 
        MultiByteToWideChar(CP_ACP, 0, tmpP, -1, wPath, MAX_PATH); 

        // Save the link by calling IPersistFile::Save. 
        hres = ppf->lpVtbl->Save(ppf, wPath, TRUE); 
    }
    

    // Cleanup
    ppf->lpVtbl->Release(ppf);
    psl->lpVtbl->Release(psl); 
    CoUninitialize();

    return hres; 
}

ResolveLinks()
{
    IShellLink* psl;

    CoInitialize(NULL);
    HRESULT hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, (LPVOID*)&psl);

    if (hres < 0) 
    {
        JBlogErr("CoCreateInstance error");
        return -1;
    }
    IPersistFile* ppf; 

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

    wchar_t wPath[MAX_PATH];
    char tmpP[MAX_PATH];
    char index[8];

    for (size_t i = 0; i < JailNum; i++)
    {
        strcpy(tmpP, path);
        sprintf(index, "%lli", i);

        strcat(tmpP, index);

        // Ensure that the string is Unicode. 
        MultiByteToWideChar(CP_ACP, 0, tmpP, -1, wPath, MAX_PATH); 

        // Save the link by calling IPersistFile::Save. 
        hres = ppf->lpVtbl->Load(ppf, wPath, STGM_READ);
        hres = psl->lpVtbl->Resolve(psl, NULL, 0);
    }
    
    JailNum = 0;
    
    // Cleanup
    ppf->lpVtbl->Release(ppf);
    psl->lpVtbl->Release(psl); 
    CoUninitialize();

    return hres; 
}