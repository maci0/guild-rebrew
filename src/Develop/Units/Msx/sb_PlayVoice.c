


// SIZE 0x30
#include "Develop/client_types.h"
typedef SOUND_VOICE Voice;

extern int sb_WaveDriver;
extern SOUND_VOICE sb_DummyVoice;
Voice* __cdecl sb_AllocVoice(void);
char* __cdecl sb_FindSampleByName(char* bank, const char* name);
int __cdecl sb_StartVoice(Voice* v, int a, int b);

/* ADDRESS: GOLDDE 0x00420290 */
Voice* __cdecl sb_PlayVoice(char* bank, const char* name, int loop, int pan, int vol, int a, int b)
{
	Voice* v;

	if (sb_WaveDriver == 0) {
		return &sb_DummyVoice;
	}
	v = sb_AllocVoice();
	if (v != 0) {
		v->sample = sb_FindSampleByName(bank, name);
		if (v->sample != 0) {
			v->loop = loop;
			v->pan = pan;
			v->vol = vol;
			sb_StartVoice(v, a, b);
		} else {
			v = 0;
		}
	}
	return v;
}
