#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;

void __cdecl ch_QueueWalkToDummyRotate(char* a, char* b);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLDDE 0x0040ba70 */
int __cdecl WalkToDummyRotateVerified(char** a, char** b, int* c)
{
	if (evt_WaitingScriptTask != 0 && *(void**) (evt_WaitingScriptTask + 0x44) == (void*) WalkToDummyRotateVerified) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) WalkToDummyRotateVerified;
		}
		return 0;
	}
	if (*b == 0 || *a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	if (DummyBlocked(b, c)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "object busy");
		return 0;
	}
	ch_QueueWalkToDummyRotate(*a, *b);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) WalkToDummyRotateVerified;
	}
	return 1;
}
