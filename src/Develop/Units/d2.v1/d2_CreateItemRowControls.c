

#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_10161cc[];

int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);

int __cdecl d2_CreateItemRowControls(int row, int id, int* out, int layer)
{
	out[1] = d2_AddElementToWindow(0, row * 120, 0x74c, layer);
	out[0] = d2_AddElementToWindow(0xd, row * 120 + 5, id, layer);
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[out[0]].value_05c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[out[0]].flags_1d0)) = 3;
	out[2] = d2_CreateChildWindow(0x40, row * 120, 0xcd, 0x57, 0x10, layer);
	g_10161cc[out[2] * 243] = 0x54;
	return out[1];
}
