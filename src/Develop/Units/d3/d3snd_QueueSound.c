#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_681750;

int* __cdecl d3snd_PrepareVoiceSample(int, int, int, int);
int __cdecl sb_SetVoiceVolume(int*, int);
void __cdecl d3snd_TrackQueuedVoice(int*, int);


/* ADDRESS: GOLDTL 0x004c30a0 */
int* __cdecl d3snd_QueueSound(int code, int arg2, int text, int variation, int delay)
{
	int* p;

	if (d3snd_SoundEnabled == 0)
		return 0;
	p = d3snd_PrepareVoiceSample(code, arg2, text, variation);
	if (p != 0) {
		sb_SetVoiceVolume(p, (int) (g_681750 * 127.0f));
		d3snd_TrackQueuedVoice(p, delay);
	}
	return p;
}
