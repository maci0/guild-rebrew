#include <math.h>
#include "Develop/Units/Msx/client_sound.h"

#include "Develop/Units/d3/d3_camera.h"
void __cdecl d3_TransformPoint(char*, char*, float*);
void __cdecl sb_SetVoiceVolume(char*, int);
int __cdecl sb_CheckVoicePlaying(char*);
void __cdecl sb_StopVoice(char*, int);
char* __cdecl sb_PrepareVoice(int, char*);
void __cdecl sb_SetVoiceLoopCount(char*, int);
void __cdecl d3snd_PlaySource(char*, int, int, int);


/* ADDRESS: GOLDDE 0x00416e10 */
void __cdecl d3_UpdateSoundSourceVolume(SOUND_SOURCE* source)
{
    float position[4];
    float x, y, z;
    float distance;
    float remaining;
    int linearVolume, curvedVolume, volume;

    if (source == 0 || source->objekt == 0) {
        return;
    }
    d3_TransformPoint(source->objekt, source->objekt + 0x4c, position);
    x = position[0] - *(float*)((char*)d3_ActiveCamera + 0x4c);
    y = position[1] - *(float*)((char*)d3_ActiveCamera + 0x50);
    z = position[2] - *(float*)((char*)d3_ActiveCamera + 0x54);
    distance = (float)sqrt(z * z + y * y + x * x);
    distance = (float)(distance * 0.025400050800101603);
    remaining = source->range - distance;
    if (remaining > 0.0f) {
        linearVolume = (int)(remaining / source->range * source->volume);
        curvedVolume = (int)(source->volume - distance * distance * source->volume / (source->range * source->range));
        volume = (int)(((linearVolume > 0 ? linearVolume : 0) + curvedVolume) * 0.5f);
    } else {
        volume = 0;
    }
    if (volume > 5) {
        if (source->voice != 0) {
            sb_SetVoiceVolume(source->voice, volume);
            if (sb_CheckVoicePlaying(source->voice) == 0 && source->playbackControl == 0) {
                source->idleCounter = 0;
                if (source->replay != 0) {
                    *(int*)(source->voice + 0x14) &= ~8;
                } else {
                    d3snd_PlaySource((char*)source, 0, 0, 0);
                }
            }
        } else {
            source->voice = sb_PrepareVoice(0, (char*)source);
            if (source->voice != 0) {
                d3snd_SetVoiceFlag0x10((int*)source->voice, 1);
                *(int*)(source->voice + 0xc) = source->playbackControl;
                *(int*)(source->voice + 0x18) = source->replay;
                sb_SetVoiceVolume(source->voice, volume);
                sb_SetVoiceLoopCount(source->voice, source->playbackControl);
                d3snd_PlaySource((char*)source, 0, source->playbackControl, source->replay);
            }
        }
    } else if (source->voice != 0) {
        sb_SetVoiceVolume(source->voice, volume);
        sb_StopVoice(source->voice, 0);
        if (source->keepVoice == 0) {
            d3snd_SetVoiceFlag0x10((int*)source->voice, 0);
            source->voice = 0;
        }
    }
}
