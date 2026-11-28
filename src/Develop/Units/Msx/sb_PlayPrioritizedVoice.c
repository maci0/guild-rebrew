


// SIZE 0x30
#include "Develop/client_types.h"
typedef SOUND_VOICE Voice;

extern int g_6b7d7c;
extern SOUND_VOICE g_14cbbe0;
Voice* __cdecl sb_AllocVoice(void);
char* __cdecl sb_FindSampleByName(char* bank, const char* name);
char* __cdecl sb_FindSampleBank(char* sample);
void __cdecl sb_LoadEntry(char* bank, char* sample);
int __cdecl sb_StartVoice(Voice* v, int a, int b);

Voice* __cdecl sb_PlayPrioritizedVoice(char* bank, const char* name, int prio, int loop, int pan, int vol, int a)
{
	Voice* v;
	char* s;

	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	v = sb_AllocVoice();
	if (v != 0) {
		s = sb_FindSampleByName(bank, name);
		v->sample = s;
		if (s != 0 && bank == 0) {
			bank = sb_FindSampleBank(s);
		}
		if (s == 0 || bank == 0 || s[0x36] != 2) {
			v = 0;
		} else {
			if (*(int**) (s + 0x38) == 0) {
				sb_LoadEntry(bank, s);
			}
			if (*(int**) (v->sample + 0x38) != 0 && prio < **(int**) (v->sample + 0x38)) {
				v->loop = loop;
				v->pan = pan;
				v->vol = vol;
				v->flags |= 4;
				v->f20 = prio;
				sb_StartVoice(v, a, 0);
			} else {
				v = 0;
			}
		}
	}
	return v;
}
