#include <windows.h>
#include "beacon.h"

DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegOpenKeyExA(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegQueryValueExA(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegCloseKey(HKEY);

void go(char * args, int alen) {
        BeaconPrintf(CALLBACK_OUTPUT, "Hello World: %s", args);
        // My code
        HKEY hKey;
    char szValue[256];
    DWORD dwSize = sizeof(szValue);
    LONG lResult;

    lResult = ADVAPI32$RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey);
    if (lResult == ERROR_SUCCESS)
    {
        lResult = ADVAPI32$RegQueryValueExA(hKey, "DisplayName", NULL, NULL, (LPBYTE)szValue, &dwSize);
        if (lResult == ERROR_SUCCESS)
        {
                        BeaconPrintf(CALLBACK_OUTPUT, "Antivirus installed: %s\n", szValue);
        }
        ADVAPI32$RegCloseKeyA(hKey);
    }
}