#include "client_types.h"

void __cdecl ResetDisplayCounters(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        d2_DisplayCounters[i].val = 0;
        d2_DisplayCounters[i].key = -1;
    }
}
