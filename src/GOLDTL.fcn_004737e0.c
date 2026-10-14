#include "client_types.h"

int __cdecl CountDisplayCounters(void)
{
    int i;
    int n;
    n = 0;
    for (i = 0; i < 6; i++) {
        if (DisplayCounters[i].key != -1) {
            n++;
        }
    }
    return n;
}
