#include "Develop/DieGildeAddOn/game/game_data.h"
extern void (__stdcall* g_6623a8)(int);

int __cdecl msx_FindWaveDriverIndex(int a1);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0042a2d0 */
int __cdecl fcn_0042a2d0(int* waveDriver)
{
    int r;
    int i;

    r = 0;
    if (g_6b7f90 != r && (i = msx_FindWaveDriverIndex((int) waveDriver)) >= r) {
        g_6623a8(*waveDriver);
        if (g_6b7f10[i] != r) {
            m_FreeTracked(g_6b7f10[i]);
            g_6b7f10[i] = r;
        }
        if (g_6b7f50[i] != r) {
            m_FreeTracked(g_6b7f50[i]);
            g_6b7f50[i] = r;
        }
        m_FreeTracked(waveDriver);
        msx_WaveDrivers[i] = r;
    } else {
        r = -1;
    }
    return r;
}
