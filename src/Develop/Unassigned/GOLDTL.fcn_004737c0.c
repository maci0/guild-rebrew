#include "client_types.h"

void __cdecl ResetDisplayCounters(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        DisplayCounters[i].val = 0;
        DisplayCounters[i].key = -1;
    }
}
