#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char* evt_CurrentScript;
extern char g_67617c[];



void __cdecl fcn_00404a00(void*, int, int, int, int, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl PreloadAnimation(void** objectRef, int* a2, int* a3, int* a4, int* a5)
{
	void* object;

	object = *objectRef;
	if (object == 0) {
		fcn_00425bf0(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_67617c);
		return 1;
	}
	fcn_00404a00(object, 4, *a2, *a3, *a4, *a5);
	return 0;
}
