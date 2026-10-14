


// SIZE 0x30
#include "client_types.h"
typedef Voice_14cbbe0 Voice;

extern int g_6b7d7c;
extern Voice_14cbbe0 g_14cbbe0;
Voice* __cdecl fcn_004229b0(void);
char* __cdecl fcn_00422530(char* bank, const char* name);
char* __cdecl fcn_004228c0(char* sample);
void __cdecl fcn_00422ad0(char* bank, char* sample);

Voice* __cdecl fcn_00422600(char* bank, const char* name, int prio)
{
	Voice* v;

	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	v = fcn_004229b0();
	if (v != 0) {
		v->sample = fcn_00422530(bank, name);
		if (v->sample != 0) {
			if (bank == 0) {
				bank = fcn_004228c0(v->sample);
			}
			if (bank != 0 && v->sample[0x36] == 2) {
				if (*(int**) (v->sample + 0x38) == 0) {
					fcn_00422ad0(bank, v->sample);
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
