#include "Develop/Units/Msx/client_sound.h"

void __cdecl FadeMasterVolume(float volume, int duration);

/* ADDRESS: GOLD 0x004c24c0 */
/* ADDRESS: GOLDDE 0x004b0840 */
void __cdecl msx_FadeMasterVolumeIfTrackActive(float volume, int duration)
{
    if (tp_msx_CurrentTrack != 0) {
        FadeMasterVolume(volume, duration);
    }
}
