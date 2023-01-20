#include <windows.h>
#include "beacon.h"

typedef LSTATUS (WINAPI *RegOpenKeyExAOverride)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY); // type de retour de la function

void go(char * args, int alen)
{
        LSTATUS hKey;
        HMODULE hModule = LoadLibraryA("Advapi32.dll");
        RegOpenKeyExAOverride func = (RegOpenKeyExAOverride) GetProcAddress(hModule, "RegOpenKeyA"); // nom de la variable definir dans le typedef

        func(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey);
        BeaconPrintf(CALLBACK_OUTPUT, "RegOpenKeyExAOverride returned: %llu\n", hKey);

        // to finish but load lib ok

        FreeLibrary(hModule);
}