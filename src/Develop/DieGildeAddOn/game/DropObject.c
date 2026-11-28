#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
int __cdecl d3_FindSceneObject(int a, int b, char* c, int d);
int __cdecl ch_QueueDropObject(char* e, char* name, char* name2, int param);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl DropObject(char** a, char** name, int* param, char** name2)
{
	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	if (*name2 != 0 && !d3_FindSceneObject(0, 0x40, *name2, 0)) {
		return 1;
	}
	if (evt_WaitingScriptTask != 0 && *(void**) (evt_WaitingScriptTask + 0x44) == (void*) DropObject) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) DropObject;
		}
		return 0;
	}
	ch_QueueDropObject(*a, *name, *name2, *param);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) DropObject;
	}
	return 0;
}
