#include <string.h>
#include "client_sound.h"



SOUND_SOURCE* __cdecl fcn_00418c80(char* voice, char* objekt, int volume, float range)
{
    SOUND_SOURCE* source = 0;
    double scaled;

    if (voice != 0 && objekt != 0 && *(SOUND_SOURCE**)(objekt + 0x210) == 0) {
        source = fcn_00418dc0();
        if (source != 0 && *(char**)(voice + 4) != 0) {
            fcn_00426170((int*)voice, 1);
            strncpy(source->name, *(char**)(voice + 4) + 4, 50);
            scaled = range * g_662b40;
            source->objekt = objekt;
            *(SOUND_SOURCE**)(objekt + 0x210) = source;
            source->voice = voice;
            source->volume = volume;
            source->range = (float)scaled;
            source->keepVoice = 1;
            fcn_004190d0(source);
            fcn_00418fb0(source);
            source->keepVoice = 0;
            source->idleCounter = 0;
        }
    }
    return source;
}


SOUND_SOURCE* __cdecl fcn_00418dc0(void)
{
	int i = 0;
	SOUND_SOURCE* r = 0;
	SOUND_SOURCE* t;
	int n;

	t = ((SOUND_SOURCE*)g_6b5d08);
	if (t != 0) {
		n = g_677680;
		for (; i < n; i++) {
			if (t[i].objekt == 0) {
				r = &t[i];
				break;
			}
		}
	}
	return r;
}
