#include "client_sound.h"

void __cdecl fcn_00420530(float volume, int duration);

/* ADDRESS: GOLD 0x004c24c0 */
void __cdecl fcn_004c24c0(float volume, int duration)
{
    if (g_772d1c != 0) {
        fcn_00420530(volume, duration);
    }
}
