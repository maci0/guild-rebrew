#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char* evt_CurrentScript;
extern char g_67617c[];



void __cdecl ch_PreloadCharacterMotions(void*, int, int, int, int, int);
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl PreloadAnimation(void** objectRef, int* a2, int* a3, int* a4, int* a5)
{
	void* object;

	object = *objectRef;
	if (object == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_67617c);
		return 1;
	}
	ch_PreloadCharacterMotions(object, 4, *a2, *a3, *a4, *a5);
	return 0;
}
