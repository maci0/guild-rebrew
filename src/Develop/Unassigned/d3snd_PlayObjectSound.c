#include "client_sound.h"

void __cdecl sb_StartVoice(char* obj, int a, int b);


int __cdecl d3snd_PlayObjectSound(char* voice, void* object, int volume, float range)
{
	SOUND_SOURCE req;
	double scaled;

	if (voice == 0 || object == 0) {
		return 0;
	}
	scaled = range * g_662b40;
	req.objekt = object;
	req.playbackControl = 1;
	req.voice = voice;
	*(int*) (voice + 0xc) = 1;
	*(int*) (voice + 0x14) = 0;
	req.volume = volume;
	req.range = (float)scaled;
	d3_UpdateSoundSourcePan(&req);
	d3_UpdateSoundSourceVolume(&req);
	if (*(int*) (voice + 0x24) == 0) {
		return 0;
	}
	sb_StartVoice(voice, 0, 0);
	return 1;
}
