#include "Develop/Units/Msx/msx.h"

int __cdecl msx_SetMasterVolume(int *handle, int volume);

/* ADDRESS: GOLD 0x00423a50 */
void __cdecl fcn_00423a50(int lautstaerke)
{
    if (msx_AmbientDriver) {
        EnterCriticalSection(&msx_TrackLock);
        msx_SetMasterVolume((int *)msx_AmbientDriver, lautstaerke);
        /* The volume slot has no named storage owner yet. */
        *(int *)0x5f74bc = lautstaerke;
        LeaveCriticalSection(&msx_TrackLock);
    }
}
