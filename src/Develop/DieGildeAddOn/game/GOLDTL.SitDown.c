#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7ebc;
extern char* evt_CurrentScript;
char* __cdecl CreateAnimationEvent(char* owner, char* name);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SitDown(char** a, char** v)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) SitDown) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) SitDown;
		}
		return 0;
	}
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	CreateAnimationEvent(*a, *v);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) SitDown;
	}
	return 0;
}
