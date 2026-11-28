#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_14a79c0[];

int __cdecl gm_GetStorageSlotCapacity(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);


/* ADDRESS: GOLDTL 0x004bf000 */
int __cdecl d2_CreateRouteWareSlot(unsigned short* a1, int a2, int a3, int col, int x, int y, int layer, int* out)
{
	int tbl[3][3] = { { 0x51, 0, 0 }, { 0x30, 0x71, 0 }, { 0x11, 0x52, 0x93 } };
	int k;
	int r;
	int id;
	int px;
	int py;

	k = gm_GetStorageSlotCapacity(a2, a3);
	px = tbl[*a1 - 0x134][col] + x + 0x6e;
	py = y + 0x22;
	r = d2_AddWindowValueGauge(px - 8, py - 5, 0x2f, 0, k, 0x6a, 0x2d, layer);
	id = d2_AddWindowField(px, py, a3 + 0xdf, 0x8a, layer);
	d2_SetElementFont(id, 0x54);
	out[0] = -1;
	out[1] = id;
	out[2] = r;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].flags_1d0)) = 0x22;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_1dc)) = 4;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_1e0)) = 0xf;
	fcn_0064d41a(((char*)&((D2_CONTROL_TL*)d2_Controls)[id] + 0x0cc), "%s", ((char**)g_14a79c0)[a3 * 2]);
	return id;
}
