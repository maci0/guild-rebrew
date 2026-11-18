#include "client_sound.h"

void __cdecl FadeMasterVolume(float volume, int duration);

/* ADDRESS: GOLD 0x004c24c0 */
void __cdecl fcn_004c24c0(float volume, int duration)
{
    if (tp_msx_CurrentTrack != 0) {
        FadeMasterVolume(volume, duration);
    }
}
