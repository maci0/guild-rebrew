#include "Develop/DieGildeAddOn/game/ch_script.h"



extern char* g_6b7ebc;
extern char* evt_CurrentScript;
int __cdecl ch_QueuePlayAnimation(char* e, char* name, int param);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl PlayAnimation(char** a, char** name, int* param)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) PlayAnimation) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) PlayAnimation;
		}
		return 0;
	}
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	ch_QueuePlayAnimation(*a, *name, *param);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) PlayAnimation;
	}
	return 0;
}
