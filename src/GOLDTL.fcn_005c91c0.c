

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int f18;
	char pad1[0x54];
	int f70;
	char pad2[0x280];
} Obj;

extern char* g_1015ea0;

#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00472900(int, int);

void __cdecl fcn_005c91c0(int a, int b, int c, int d, int e)
{
	int idx;

	idx = d2_ShowTxt(b, c, (char*) a, *(int*) 0x772514);
	((Obj*)g_1015ea0)[idx].f70 = 0;
	((Obj*)g_1015ea0)[idx].f18 = d;
	fcn_00472900(idx, e);
}
