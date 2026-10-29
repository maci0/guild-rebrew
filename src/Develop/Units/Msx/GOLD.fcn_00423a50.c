#include "Develop/Units/Msx/msx.h"

int __cdecl fcn_0042a0e0(int *handle, int volume);

/* ADDRESS: GOLD 0x00423a50 */
void __cdecl fcn_00423a50(int lautstaerke)
{
    if (g_6b71a8) {
        EnterCriticalSection(&g_14cc5a0);
        fcn_0042a0e0((int *)g_6b71a8, lautstaerke);
        /* The volume slot has no named storage owner yet. */
        *(int *)0x5f74bc = lautstaerke;
        LeaveCriticalSection(&g_14cc5a0);
    }
}
