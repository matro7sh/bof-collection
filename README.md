# bof-collection
Collection of beacon object file (Cobalt strike)

>files with suffix "ll" correspond to beacon object file using the library load

## How to compile

>Install mingw64 (this works on kali too, no need windows)


`x86_64-w64-mingw32-gcc.exe -o Z:\getAV.o -c Z:\getAV.c`


## How to use with Cobalt

`inline-execute /PathToFile.o`


## How to write BoF (prototype way)

if you need the `RegCloseKey` function

look at the Windows documentation (in our example https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regclosekey) to get the list of the aguments

in our case : 

```
LSTATUS RegCloseKey(
  [in] HKEY hKey
);
``` 

Then, get the name of the library used (at the bottom of the page) in our case it is : `Advapi32.lib`

we have to structure it like this : 
`DECLSPEC_IMPORT LSTATUS WINAPI <lib>$<Function>(<Args List>);`

still in our case, we will get this: 
`DECLSPEC_IMPORT LSTATUS WINAPI ADVAPI32$RegCloseKey(HKEY);`

you just have to use the function like this in our code : `ADVAPI32$RegCloseKeyA(hKey);`


### Preview 
![](/img/preview.png)


>Authors : @LeDocteurDesBits, @jenaye_fr