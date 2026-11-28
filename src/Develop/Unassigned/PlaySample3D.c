


extern char* evt_CurrentScript;
extern int evt_ActiveContextId;
int __cdecl sb_PrepareVoice(int a, int b);
int __cdecl sb_StartVoice(int o, int a, int b);
void __cdecl sb_SetVoiceLoopCount(int o, int v);
#include "Develop/Units/Msx/client_sound.h"

int __cdecl PlaySample3D(int* a, int* b, int* c, int* d)
{
	int o;

	if (*(int*) (evt_CurrentScript + 0x104) != evt_ActiveContextId) {
		return 0;
	}
	o = sb_PrepareVoice(0, *c);
	if (o != 0) {
		if (*d == 1) {
			d3snd_PlayObjectSound((char*)o, (void*)*a, 0x3c, (float) *b);
		} else {
			sb_SetVoiceLoopCount(o, *d);
			sb_StartVoice(o, 0, 0);
		}
	}
	return o;
}
