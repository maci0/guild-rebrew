


// SIZE 0x30
#include "client_types.h"
typedef SOUND_VOICE Voice;

extern int g_6b7d7c;
extern SOUND_VOICE g_14cbbe0;
Voice* __cdecl sb_AllocVoice(void);
char* __cdecl sb_FindSampleByName(char* bank, const char* name);
char* __cdecl sb_FindSampleBank(char* sample);
void __cdecl sb_LoadEntry(char* bank, char* sample);

Voice* __cdecl sb_PreparePrioritizedVoice(char* bank, const char* name, int prio)
{
	Voice* v;

	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	v = sb_AllocVoice();
	if (v != 0) {
		v->sample = sb_FindSampleByName(bank, name);
		if (v->sample != 0) {
			if (bank == 0) {
				bank = sb_FindSampleBank(v->sample);
			}
			if (bank != 0 && v->sample[0x36] == 2) {
				if (*(int**) (v->sample + 0x38) == 0) {
					sb_LoadEntry(bank, v->sample);
				}
				if (*(int**) (v->sample + 0x38) != 0 && prio < **(int**) (v->sample + 0x38)) {
					v->loop = 1;
					v->flags |= 4;
					v->pan = 0x3f;
					v->vol = 0x7f;
					v->f20 = prio;
					return v;
				}
			}
		}
	}
	return 0;
}
