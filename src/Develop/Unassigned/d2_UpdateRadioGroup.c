#include "client_data.h"
extern D2_RADIO_GROUP g_102cbc4[8];
extern int g_14ce904, g_14ce900, d2_CurrentElementId, g_67d38c, g_14ce8d8, g_14ce8cc; void __cdecl d2_SelectRadioGroup(int, int); int __cdecl io_SetMouseCursorPos(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00469630 */
void __cdecl d2_UpdateRadioGroup(int groupIndex)
{
	int count;
	int sel;
	int i;
	int alt;
	int id;
	char key;

	count = g_102cbc4[groupIndex].count;
	if (count <= 0) {
		return;
	}
	sel = g_102cbc4[groupIndex].sel;
	if (*(int*) 0x67d3d0) {
		goto scan;
	}
	if (*(int*) 0x6b8af8 != (int) g_14ce8c0
		|| *(int*) 0x6b8afc != (int) g_14ce8c2) {
		*(int*) 0x67d3d0 = 1;
scan:
		if (!tp_d2_SelectedControl) {
			for (i = 0; i < count; i++) {
				if (g_102cbc4[groupIndex].ids[i] == d2_CurrentElementId
					&& (!(*(unsigned char*) (groupIndex * 0x8c + (unsigned long)&g_102cbc0) & 1)
						|| g_14ce8cc)) {
					sel = i;
				}
			}
			if (sel == g_102cbc4[groupIndex].sel) {
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
		id = g_102cbc4[groupIndex].ids[sel];
		alt = (char*) &((D2_CONTROL_TL*) g_1015ea0)[id];
		io_SetMouseCursorPos(
			(int) (((D2_CONTROL_TL*) alt)->width * 0.5
				+ ((D2_CONTROL_TL*) alt)->x),
			(int) (((D2_CONTROL_TL*) alt)->height * 0.5
				+ ((D2_CONTROL_TL*) alt)->y));
	}
skip:
	if (sel == -1) {
		if (g_102cbc4[groupIndex].sel != -1) {
			d2_SelectRadioGroup(groupIndex, -1);
		}
		return;
	}
	if (sel < 0) {
		sel = g_102cbc4[groupIndex].count - 1;
	}
	sel %= g_102cbc4[groupIndex].count;
	if (sel != g_102cbc4[groupIndex].sel || !*(int*) 0x67d3d0) {
		d2_SelectRadioGroup(groupIndex, sel);
	}
	if (g_14cf950 != 0x1c) {
		return;
	}
	g_14ce8d8 = 1;
	g_14cf950 = 0;
	id = g_102cbc4[groupIndex].ids[sel];
	d2_CurrentElementId = id;
	alt = (char*) &((D2_CONTROL_TL*) g_1015ea0)[id];
	if (((D2_CONTROL_TL*) alt)->kind != 9) {
		g_100f1dc = ((D2_CONTROL_TL*) alt)->value_008;
	}
	else {
		g_100f1dc = (*(unsigned char*) &((D2_CONTROL_TL*) alt)->flags_1d0 & 0x10) ? 1 : 2;
	}
}
