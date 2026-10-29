


// SIZE 0x30
#include "client_types.h"
typedef Voice_14cbbe0 Voice;

extern int g_6b7d7c;
extern Voice_14cbbe0 g_14cbbe0;
Voice* __cdecl fcn_004229b0(void);
char* __cdecl fcn_00422530(char* bank, const char* name);
char* __cdecl fcn_004228c0(char* sample);
void __cdecl sb_LoadEntry(char* bank, char* sample);
int __cdecl fcn_00423670(Voice* v, int a, int b);

Voice* __cdecl fcn_004235b0(char* bank, const char* name, int prio, int loop, int pan, int vol, int a)
{
	Voice* v;
	char* s;

	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	v = fcn_004229b0();
	if (v != 0) {
		s = fcn_00422530(bank, name);
		v->sample = s;
		if (s != 0 && bank == 0) {
			bank = fcn_004228c0(s);
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
				fcn_00423670(v, a, 0);
			} else {
				v = 0;
			}
		}
	}
	return v;
}
