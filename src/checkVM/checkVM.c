#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "beacon.h"

void go(char * args, int alen)

{
	(void) args;
	(void) alen;
	
    uint32_t eax, ebx, ecx, edx;
    int is_vm = 0;

    __asm__ __volatile__ (
        "cpuid"
        : "=a" (eax),
          "=b" (ebx),
          "=c" (ecx),
          "=d" (edx)
        : "a" (1)
    );

    if (ecx & 0x80000000) {
        is_vm = 1;
    }

    if (is_vm) {
		 BeaconPrintf(CALLBACK_OUTPUT, "This is a virtual machine\n");
    } else {
       BeaconPrintf(CALLBACK_OUTPUT, "This is not a virtual machine\n");
    }

    return 0;
}