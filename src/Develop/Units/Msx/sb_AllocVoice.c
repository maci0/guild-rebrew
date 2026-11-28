


// SIZE 0x30
#include "Develop/client_types.h"
typedef SOUND_VOICE Voice;

extern int sb_WaveDriver;
extern SOUND_VOICE sb_DummyVoice;
extern char* sb_Voices;
#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_GetSampleStatus(int h);
void __cdecl msx_InitSample(int h);

Voice* __cdecl sb_AllocVoice(void)
{
	Voice* best;
	int i;

	best = 0;
	if (sb_WaveDriver == 0) {
		return &sb_DummyVoice;
	}
	if (((Voice*)sb_Voices) != 0) {
		for (i = 0; i < sb_VoiceCount; i++) {
			if (msx_GetSampleStatus(((Voice*)sb_Voices)[i].h) != 4 && (((Voice*)sb_Voices)[i].flags & 0x10) == 0) {
				best = &((Voice*)sb_Voices)[i++];
				break;
			}
		}
		if (best != 0) {
			for (; i < sb_VoiceCount; i++) {
				if (((Voice*)sb_Voices)[i].prio < best->prio && msx_GetSampleStatus(((Voice*)sb_Voices)[i].h) != 4 &&
				    (((Voice*)sb_Voices)[i].flags & 0x10) == 0) {
					best = &((Voice*)sb_Voices)[i];
				}
			}
			msx_InitSample(best->h);
			best->flags = 0;
			best->f18 = 0;
			best->loop = 1;
		}
	}
	return best;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_6b7d7c[268];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_6b7d8c[252];
#endif
