#include "Develop/Units/Msx/msx.h"

int __cdecl fcn_0042a0e0(int *handle, int volume);

/* ADDRESS: GOLD 0x00423a50 */
void __cdecl fcn_00423a50(int lautstaerke)
{
    if (msx_AmbientDriver) {
        EnterCriticalSection(&msx_TrackLock);
        fcn_0042a0e0((int *)msx_AmbientDriver, lautstaerke);
        /* The volume slot has no named storage owner yet. */
        *(int *)0x5f74bc = lautstaerke;
        LeaveCriticalSection(&msx_TrackLock);
    }
}
