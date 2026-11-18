#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7ebc;
extern char* evt_CurrentScript;
int __cdecl fcn_00445600(int a, int b, char* c, int d);
int __cdecl fcn_00406c70(char* e, char* name, char* name2, int param);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl DropObject(char** a, char** name, int* param, char** name2)
{
	if (*a == 0) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	if (*name2 != 0 && !fcn_00445600(0, 0x40, *name2, 0)) {
		return 1;
	}
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) DropObject) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (evt_CurrentScript + 0xc60) = (void*) DropObject;
		}
		return 0;
	}
	fcn_00406c70(*a, *name, *name2, *param);
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(void**) (evt_CurrentScript + 0xc60) = (void*) DropObject;
	}
	return 0;
}
