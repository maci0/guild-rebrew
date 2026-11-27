extern char* g_77255c;
extern char* g_1015ea0;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

void* __cdecl gm_SearchTable67(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl fcn_0050c7d0(int, int);
int __cdecl gm_GetBuildingTechEffect(unsigned char*, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetControlText(int, char*);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl fcn_00526120(void*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_SetGroupVisibility(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetElementValue(int, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005c3820 */
void __cdecl d2_ShowTechTreeEffects(unsigned char* building, unsigned char* a1)
{
	int table[37] = { 1, 2, 0xb, 0xc, 9, 5, 6, 3, 4, 0xa, 0xd, 0xe, 0xf,
		0x10, 0x11, 7, 8, 0 };
	int elems[37];
	int wins[37];
	char buf[1024];
	int count;
	int window;
	int elem;
	int label;
	int gauge;
	int found;
	int id;
	int step;
	int height;
	int i;
	int entry;
	int type;

	id = *(int*) (building + 1);
	for (i = 0; i < 0x24; i++) {
		table[i] = i + 1;
	}
	for (i = 0; i < 0x25; i++) {
		elems[i] = -1;
	}
	table[0x24] = 0;
	window = d2_LoadForm(0, 0, "techtree\\auswirkungen");
	d2_CenterDialogWindows(window);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(window, 1);
	io_AppendText(0x17e0, building);
	d2_SetForm(window, 3);
	elem = d2_GetWindowListItem(window, 3, io_AppendText(0x17e1));
	d2_SetForm(window, 2);
	entry = table[0];
	count = 0;
	if (entry != 0) {
		for (i = 0; table[i] != 0; i++) {
			if (fcn_0050c7d0(building[0], table[i]) != 0) {
				count++;
			}
		}
	}
	step = (int) (10.0f / count * 24.0f);
	height = (*(int*) (g_77255c + 0x10) - step * count) / 2 + 0xe;
	for (i = 0; table[i] != 0; i++) {
		if (fcn_0050c7d0(building[0], table[i]) != 0) {
			label = d2_AddElementToWindow(0, height, 2, d2_CurrentWindowId);
			wins[i] = label;
			((D2_CONTROL_TL*) (g_1015ea0))[label].flags_1d0 = 3;
			((D2_CONTROL_TL*) (g_1015ea0))[label].font = 0x55;
			io_FormatTextBuffer(buf, "%s:", *(unsigned int*) (table[i] * 8 + 0x14a9180));
			d2_SetControlText(label, buf);
			((D2_CONTROL_TL*) (g_1015ea0))[label].value_05c = 1;
			if (table[i] == 3) {
				type = 6;
			}
			else if (table[i] == 0x24) {
				type = 4;
			}
			else {
				type = fcn_0050c7d0(building[0], table[i]);
			}
			gauge = d2_AddWindowValueGauge(0x140, height, 0x82, 0, type, 0x6f, 0x56, d2_CurrentWindowId);
			elems[i] = gauge;
			d2_SetElementValue(gauge, 0, type, 0, 0);
			height += step;
		}
		else {
			wins[i] = -1;
		}
	}
	g_100f1dc = -1;
	for (;;) {
		found = (int) gm_SearchTable67(id);
		if ((a1[0x5b] & 4) != 0 || found == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0 || (g_100f1dc != -1 && elem == d2_CurrentElementId)) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			for (i = 0; table[i] != 0; i++) {
				if (wins[i] != -1 && d2_CurrentElementId == wins[i]) {
					io_FormatTextBuffer(buf, "$Z$[%s$]$N%s", table[i] * 2 + 0xf98,
					    table[i] * 2 + 0xf99);
					d2_SetGroupVisibility(window, 0);
					fcn_00526120(buf, 0x10);
					d2_SetGroupVisibility(window, 1);
				}
			}
		}
		for (i = 0; table[i] != 0; i++) {
			if (fcn_0050c7d0(building[0], table[i]) != 0 && elems[i] != -1) {
				if (table[i] == 3) {
					type = 6;
				}
				else if (table[i] == 0x24) {
					type = 4;
				}
				else {
					type = fcn_0050c7d0(building[0], table[i]);
				}
					{
						int v0;
						int v1;
						gm_GetBuildingTechEffect((unsigned char*) building, table[i], 0);
						v0 = gm_GetBuildingTechEffect((unsigned char*) building, table[i], 0);
						v1 = gm_GetBuildingTechEffect((unsigned char*) building, table[i], 1);
						d2_SetElementValue(elems[i], 0, type, v1, v0);
					}
			}
		}
		if (main_RunFrameLoop((void*) d2_ShowTechTreeEffects, 0x677c7) == 0) {
			d2_DestroyForm(window);
			return;
		}
	}
}
