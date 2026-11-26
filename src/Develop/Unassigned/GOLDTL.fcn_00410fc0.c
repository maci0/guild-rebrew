


extern char* evt_CurrentScript;
extern int g_6791c8;
int __cdecl fcn_00422460(int a, int b);
int __cdecl fcn_00423670(int o, int a, int b);
void __cdecl sb_SetVoiceLoopCount(int o, int v);
#include "client_sound.h"

int __cdecl PlaySample3D(int* a, int* b, int* c, int* d)
{
	int o;

	if (*(int*) (evt_CurrentScript + 0x104) != g_6791c8) {
		return 0;
	}
	o = fcn_00422460(0, *c);
	if (o != 0) {
		if (*d == 1) {
			d3snd_PlayObjectSound((char*)o, (void*)*a, 0x3c, (float) *b);
		} else {
			sb_SetVoiceLoopCount(o, *d);
			fcn_00423670(o, 0, 0);
		}
	}
	return o;
}
