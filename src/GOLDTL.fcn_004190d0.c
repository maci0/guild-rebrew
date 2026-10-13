#include <math.h>
#include "client_sound.h"

extern char* g_6b8014;
void __cdecl fcn_00455350(char*, char*, float*);
void __cdecl fcn_00423890(char*, int);
int __cdecl fcn_00423460(char*);
void __cdecl fcn_004237f0(char*, int);
char* __cdecl fcn_00422460(int, char*);
void __cdecl fcn_004238f0(char*, int);
void __cdecl fcn_004192b0(char*, int, int, int);


void __cdecl fcn_004190d0(SOUND_SOURCE* source)
{
    float position[4];
    float x, y, z;
    float distance;
    float remaining;
    int linearVolume, curvedVolume, volume;

    if (source == 0 || source->objekt == 0) {
        return;
    }
    fcn_00455350(source->objekt, source->objekt + 0x4c, position);
    x = position[0] - *(float*)((char*)g_6b8014 + 0x4c);
    y = position[1] - *(float*)((char*)g_6b8014 + 0x50);
    z = position[2] - *(float*)((char*)g_6b8014 + 0x54);
    distance = sqrt(z * z + y * y + x * x);
    distance *= g_662b40;
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
            fcn_00423890(source->voice, volume);
            if (fcn_00423460(source->voice) == 0 && source->playbackControl == 0) {
                source->idleCounter = 0;
                if (source->replay != 0) {
                    *(int*)(source->voice + 0x14) &= ~8;
                } else {
                    fcn_004192b0((char*)source, 0, 0, 0);
                }
            }
        } else {
            source->voice = fcn_00422460(0, (char*)source);
            if (source->voice != 0) {
                fcn_00426170((int*)source->voice, 1);
                *(int*)(source->voice + 0xc) = source->playbackControl;
                *(int*)(source->voice + 0x18) = source->replay;
                fcn_00423890(source->voice, volume);
                fcn_004238f0(source->voice, source->playbackControl);
                fcn_004192b0((char*)source, 0, source->playbackControl, source->replay);
            }
        }
    } else if (source->voice != 0) {
        fcn_00423890(source->voice, volume);
        fcn_004237f0(source->voice, 0);
        if (source->keepVoice == 0) {
            fcn_00426170((int*)source->voice, 0);
            source->voice = 0;
        }
    }
}
