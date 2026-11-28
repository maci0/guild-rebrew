#include "Develop/Units/Msx/client_sound.h"

#include "Develop/Units/d3/client_lighting.h"
SOUND_VOICE* __cdecl sb_PrepareVoice(int a, int b);

/* ADDRESS: GOLDDE 0x0040bc90 */
void __cdecl PlayEntitySound(char* cmd)
{
    char* e;
    SOUND_VOICE* r;

    e = *(char**)(cmd + 0x14);
    r = sb_PrepareVoice(0, (int)(cmd + 0x130));
    if (r != 0) {
        if (d3_CurrentFloor != 0) {
            d3snd_PlayObjectSound((char*)r, *(void**)(e + 0x34), 0x7f, 3000.0f);
        } else {
            d3snd_PlayObjectSound((char*)r, *(void**)(e + 0x34), 0x7f, 1000.0f);
        }
    }
}
