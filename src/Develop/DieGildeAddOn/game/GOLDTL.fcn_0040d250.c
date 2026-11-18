#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char g_675f80[];



int __cdecl fcn_004032b0(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
extern char* evt_CurrentScript;
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl GetCharacterHandle(int* id)
{
	char buf[0x80];
	int r;

	r = fcn_004032b0(*id);
	if (r == 0) {
		fcn_0064d41a(buf, g_675f80, *id);
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), buf);
	}
	return r;
}
