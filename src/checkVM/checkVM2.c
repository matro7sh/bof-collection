#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "beacon.h"


#define THRESHOLD 5000


uint64_t getTime()
{
    uint32_t l, h;

    __asm__ __volatile__("rdtsc" : "=a" (l), "=d" (h));

    return ((uint64_t) h << 32) | l;
}

void go(char * args, int alen)
{
	uint64_t delta;
    uint64_t t1 = getTime(), t2 = 0;

    __asm__ __volatile__("cpuid");
    t2 = getTime();
    
    BeaconPrintf(CALLBACK_OUTPUT, "t2 = %llu\n", t2);
    BeaconPrintf(CALLBACK_OUTPUT, "t1 = %llu\n", t1);
    BeaconPrintf(CALLBACK_OUTPUT, "Delta = %llu\n", t2 - t1);

    if (t2 - t1 > THRESHOLD)
    {
        BeaconPrintf(CALLBACK_OUTPUT, "This is a virtual machine %llu\n", delta);
    }
    else
    {
        BeaconPrintf(CALLBACK_OUTPUT, "This is not a virtual machine %llu\n", delta);
    }
}
