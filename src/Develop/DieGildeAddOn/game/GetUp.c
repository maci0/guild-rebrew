#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
char* __cdecl ch_QueueStandUpAnimation(char* e, int v);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl GetUp(char** a, int* v)
{
	if (evt_WaitingScriptTask != 0 && *(void**) (evt_WaitingScriptTask + 0x44) == (void*) GetUp) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) GetUp;
		}
		return 0;
	}
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	ch_QueueStandUpAnimation(*a, *v);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) GetUp;
	}
	return 0;
}
