#include "Develop/DieGildeAddOn/game/ch_script.h"

extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
char* __cdecl CreateAnimationEvent(char* owner, char* name);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SitDownAtOnce(char** a, char** v)
{
	char* r;

	if (evt_WaitingScriptTask != 0 && *(void**) (evt_WaitingScriptTask + 0x44) == (void*) SitDownAtOnce) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) SitDownAtOnce;
		}
		return 0;
	}
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	r = CreateAnimationEvent(*a, *v);
	if (r != 0) {
		*(int*) (r + 0x18c) |= 1;
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) SitDownAtOnce;
	}
	return 0;
}
