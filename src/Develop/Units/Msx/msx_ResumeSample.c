#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_FindSampleHandleIndex(int a);

/* ADDRESS: GOLDTL 0x0042a850 */
/* ADDRESS: GOLDDE 0x00425050 */
int __cdecl msx_ResumeSample(int a)
{
    int r = 0;

    if (msx_Initialized != 0) {
        if (msx_FindSampleHandleIndex(a) >= 0) {
            (*(void (__stdcall **)(int)) 0x6623cc)(a);
        } else {
            r = -1;
        }
    } else {
        r = -1;
    }
    return r;
}
