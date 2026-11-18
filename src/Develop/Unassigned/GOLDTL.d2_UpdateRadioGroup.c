#include "client_data.h"
extern Group_102cbc4 g_102cbc4[8];
extern int g_14ce904, g_14ce900, d2_CurrentElementId, g_67d38c, g_14ce8d8, g_14ce8cc;
void __cdecl d2_SelectRadioGroup(int, int); int __cdecl fcn_004125c0(int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00469630 */
void __cdecl d2_UpdateRadioGroup(int a0)
{
	int count;
	int sel;
	int i;
	int alt;
	int id;
	char key;

	count = g_102cbc4[a0].count;
	if (count <= 0) {
		return;
	}
	sel = g_102cbc4[a0].sel;
	if (*(int*) 0x67d3d0) {
		goto scan;
	}
	if (*(int*) 0x6b8af8 != (int) g_14ce8c0
		|| *(int*) 0x6b8afc != (int) g_14ce8c2) {
		*(int*) 0x67d3d0 = 1;
scan:
		if (!tp_d2_SelectedControl) {
			for (i = 0; i < count; i++) {
				if (g_102cbc4[a0].ids[i] == d2_CurrentElementId
					&& (!(*(unsigned char*) (a0 * 0x8c + (unsigned long)&g_102cbc0) & 1)
						|| g_14ce8cc)) {
					sel = i;
				}
			}
			if (sel == g_102cbc4[a0].sel) {
				*(int*) 0x67d3d0 = 0;
			}
		}
	}
	key = g_14cf950;
	id = g_67d38c;
	if (key == (char) 0xc8 || (g_14ce904 && id == -1)) {
		sel--;
		alt = g_14ce904;
	}
	else if (key == (char) 0xd0 || (g_14ce900 && id == -1)) {
		sel++;
		alt = g_14ce900;
	}
	else {
		goto skip;
	}
	*(int*) 0x67d3d0 = 0;
	*(int*) 0x6b8af8 = g_14ce8c0;
	*(int*) 0x6b8afc = g_14ce8c2;
	if (sel < 0) {
		sel = count - 1;
	}
	sel %= count;
	if (alt) {
		id = g_102cbc4[a0].ids[sel];
		alt = *(int*) &g_1015ea0 + id * 0x2f4;
		fcn_004125c0(
			(int) (*(int*) (alt + 0x18) * g_662908
				+ *(int*) (alt + 0x10)),
			(int) (*(int*) (alt + 0x1c) * g_662908
				+ *(int*) (alt + 0x14)));
	}
skip:
	if (sel == -1) {
		if (g_102cbc4[a0].sel != -1) {
			d2_SelectRadioGroup(a0, -1);
		}
		return;
	}
	if (sel < 0) {
		sel = g_102cbc4[a0].count - 1;
	}
	sel %= g_102cbc4[a0].count;
	if (sel != g_102cbc4[a0].sel || !*(int*) 0x67d3d0) {
		d2_SelectRadioGroup(a0, sel);
	}
	if (g_14cf950 != 0x1c) {
		return;
	}
	g_14ce8d8 = 1;
	g_14cf950 = 0;
	id = g_102cbc4[a0].ids[sel];
	d2_CurrentElementId = id;
	alt = *(int*) &g_1015ea0 + id * 0x2f4;
	if (*(int*) (alt + 0x20) != 9) {
		g_100f1dc = *(int*) (alt + 8);
	}
	else {
		g_100f1dc = (*(unsigned char*) (alt + 0x1d0) & 0x10) ? 1 : 2;
	}
}
