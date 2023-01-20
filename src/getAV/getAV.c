#include <stdio.h>
#include <windows.h>
#include "beacon.h"

DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegOpenKeyExA(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegQueryValueExA(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegCloseKey(HKEY);
DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegEnumKeyExA(HKEY, DWORD, LPSTR, LPDWORD, LPDWORD, LPSTR, LPWORD, PFILETIME);


void go(char * args, int alen)
{
	(void) args;
	(void) alen;
	
    // Get the list of installed anti-virus programs
    HKEY hKey;
    LONG lResult = ADVAPI32$RegOpenKeyExA(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
        0, KEY_READ, &hKey);
    if (lResult != ERROR_SUCCESS)
    {
        BeaconPrintf(CALLBACK_OUTPUT, "Error opening registry key\n");
    }

    // Enumerate the subkeys
    DWORD dwIndex = 0;
    char szSubkeyName[256];
    DWORD dwNameSize = sizeof(szSubkeyName);
    while (ADVAPI32$RegEnumKeyExA(hKey, dwIndex, szSubkeyName, &dwNameSize,
        NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        // Check if the subkey is an anti-virus program
        HKEY hSubkey;
        lResult = ADVAPI32$RegOpenKeyExA(hKey, szSubkeyName, 0, KEY_READ, &hSubkey);
        if (lResult != ERROR_SUCCESS)
        {
            BeaconPrintf(CALLBACK_OUTPUT, "Error opening subkey\n");
        }

        char szDisplayName[256];
        DWORD dwType;
        DWORD dwDataSize = sizeof(szDisplayName);
        lResult = ADVAPI32$RegQueryValueExA(hSubkey, "DisplayName", NULL, &dwType,
            (LPBYTE)szDisplayName, &dwDataSize);
        if (lResult == ERROR_SUCCESS && dwType == REG_SZ)
        {
            BeaconPrintf(CALLBACK_OUTPUT, "%s\n", szDisplayName);
        }

        ADVAPI32$RegCloseKey(hSubkey);

        dwIndex++;
        dwNameSize = sizeof(szSubkeyName);
    }

    ADVAPI32$RegCloseKey(hKey);
}