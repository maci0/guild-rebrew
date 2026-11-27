

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
void __cdecl d2_SetElementFont(int, int);

void __cdecl d2_ShowWrappedText(int text, int x, int y, int d, int e)
{
	int idx;

	idx = d2_ShowTxt(x, y, (char*) text, *(int*) 0x772514);
	((D2_CONTROL_TL*)g_1015ea0)[idx].value_070 = 0;
	((D2_CONTROL_TL*)g_1015ea0)[idx].width = d;
	d2_SetElementFont(idx, e);
}
