#include "Develop/DieGildeAddOn/game/ch_script.h"


extern char* g_6b7ebc;
extern char* g_6b7e98;
int __cdecl fcn_00445600(int a, int b, char* c, int d);
int __cdecl fcn_00406d10(char* e, char* name, char* name2, int param);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040d640(char** a, char** name, int* param, char** name2)
{
	if (*a == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	if (*name2 != 0 && !fcn_00445600(0, 0x40, *name2, 0)) {
		return 1;
	}
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040d640) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040d640;
		}
		return 0;
	}
	fcn_00406d10(*a, *name, *name2, *param);
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040d640;
	}
	return 0;
}
