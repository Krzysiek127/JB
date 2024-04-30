//#pragma balls
/*
*   Made by the Akadamia Pranków Cheetos
*/


#include "Funnies.h"
// pragma my nigga
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

typedef struct
{
    char *keyPtr, *valuePtr;
    int keyLen, valueLen;
} KV;

KV *scanner(char *str)
{
    int space = strchr(str, ' ') - str; // I hope this works

    KV *tmp = calloc(1, sizeof(KV));

    tmp->keyPtr = str;
    tmp->keyLen = space;
    tmp->valuePtr = str + space + 1;
    tmp->valueLen = strlen(str) - space - 1;

    return tmp;
}

//read line from file
KV *readLF(FILE *fp) {
    char c;
    char buf[256];
    int p = 0;

    while (c = fgetc(fp) && !feof(fp))
    {
        if (c == '\n') {
            return scanner(buf);
        }
        buf[p++] = c;
    }
}

char *convert(char *str, int len)
{
    char *t = calloc(len, 1);
    memcpy(t, str, len);
    t[len] = '\0';
    return t;
}


int main(int argc, char *argv[])
{
    HWND window = GetConsoleWindow();
    ShowWindow(window, SW_MINIMIZE);
    ShowWindow(window, SW_HIDE);

    //KV *r = scanner("volume 50");
    //printf("[%s:%d] = [%s:%d]\n", r->keyPtr, r->keyLen, r->valuePtr, r->valueLen);


    FILE *fp = fopen("config.cfg", "r");
    
    while (!feof(fp)) {
        KV *configLine = readLF(fp);
        
        char *value = convert(configLine->keyPtr, configLine->keyLen);

        if (!strcmp(value, "volume"))
        {
            waveOutGetVolume(NULL, (DWORD) atoi(value));
        }
    }
    
    changeWallpaper(L"C:\\Users\\Krzysiek\\Desktop\\Wallpapers 2\\HLwallpaper01_16x9.jpg");
    
    return 0;
}