


#include <stdlib.h>

// SIZE 0x30
#include "client_types.h"
typedef Voice_14cbbe0 Voice;

extern int g_6b7d7c;
extern Voice_14cbbe0 g_14cbbe0;
Voice* __cdecl fcn_004229b0(void);
char* __cdecl fcn_00422530(int a, int b);
void __cdecl fcn_0042a920(int h, int v);
void __cdecl fcn_0042a9a0(int h, int v);
void __cdecl fcn_0042aa20(int h, int v);

Voice* __cdecl fcn_00422460(int a, int b)
{
	Voice* v;

	if (g_6b7d7c != 0) {
		v = fcn_004229b0();
		if (v != 0) {
			v->sample = fcn_00422530(a, b);
			if (v->sample != 0) {
				v->f2c = 0;
				v->loop = 1;
				v->pan = abs(0x7f) / 2;
				v->vol = 0x7f;
				fcn_0042a920(v->h, 0x7f);
				fcn_0042a9a0(v->h, v->pan);
				fcn_0042aa20(v->h, v->loop);
			} else {
				v = 0;
			}
		}
		return v;
	}
	return &g_14cbbe0;
}
