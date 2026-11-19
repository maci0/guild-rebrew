#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7ebc;
extern char* evt_CurrentScript;

void __cdecl ch_QueueWalkToDummy(char* a, char* b);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl WalkToDummyVerified(char** a, char** b, int* c)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) WalkToDummyVerified) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) WalkToDummyVerified;
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
	ch_QueueWalkToDummy(*a, *b);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) WalkToDummyVerified;
	}
	return 1;
}
