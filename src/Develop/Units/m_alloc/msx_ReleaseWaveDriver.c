#include "Develop/DieGildeAddOn/game/game_data.h"
extern void (__stdcall* g_6623a8)(int);

int __cdecl msx_FindWaveDriverIndex(int a1);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0042a2d0 */
/* ADDRESS: GOLDDE 0x00424c60 */
int __cdecl msx_ReleaseWaveDriver(int* waveDriver)
{
    int r;
    int i;

    r = 0;
    if (msx_Initialized != r && (i = msx_FindWaveDriverIndex((int) waveDriver)) >= r) {
        g_6623a8(*waveDriver);
        if (msx_SampleHandles[i] != r) {
            m_FreeTracked(msx_SampleHandles[i]);
            msx_SampleHandles[i] = r;
        }
        if (msx_StreamHandles[i] != r) {
            m_FreeTracked(msx_StreamHandles[i]);
            msx_StreamHandles[i] = r;
        }
        m_FreeTracked(waveDriver);
        msx_WaveDrivers[i] = r;
    } else {
        r = -1;
    }
    return r;
}
