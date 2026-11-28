extern char g_772514[];


// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int f18;
	char pad1[0x54];
	int f70;
	char pad2[0x280];
} Obj;

extern char* d2_Controls;

#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);

/* ADDRESS: GOLDDE 0x005aafc0 */
void __cdecl d2_CreateRightAlignedText(int text, int b, int c, int d, int e)
{
	int idx;

	idx = d2_ShowTxt(b - d, c, (char*) text, *(int*) &g_772514);
	((D2_CONTROL_TL*) d2_Controls)[idx].value_070 = 1;
	((D2_CONTROL_TL*) d2_Controls)[idx].width = d;
	d2_SetElementFont(idx, e);
}
