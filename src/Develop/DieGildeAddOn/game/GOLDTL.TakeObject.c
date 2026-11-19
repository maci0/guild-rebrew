#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7ebc;
extern char* evt_CurrentScript;
int __cdecl ch_QueueTakeObject(char* e, char* name, char* src, int param);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl TakeObject(char** a, char** name, int* param, char** src)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) TakeObject) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) TakeObject;
		}
		return 0;
	}
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	if (*src == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid source");
		return 1;
	}
	ch_QueueTakeObject(*a, *name, *src, *param);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) TakeObject;
	}
	return 0;
}
