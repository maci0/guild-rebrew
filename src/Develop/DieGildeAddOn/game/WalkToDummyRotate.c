#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7ebc;
extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl ch_QueueWalkToDummyRotate(char* a, char* b);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl WalkToDummyRotate(char** a, char** b)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) WalkToDummyRotate) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) WalkToDummyRotate;
		}
		return 0;
	}
	if (*b == 0 || *a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	if (!m_is_tracked(*b)) {
		return 0;
	}
	if (!m_is_tracked(*a)) {
		return 0;
	}
	ch_QueueWalkToDummyRotate(*a, *b);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) WalkToDummyRotate;
	}
	return 1;
}
