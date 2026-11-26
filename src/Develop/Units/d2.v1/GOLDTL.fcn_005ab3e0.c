#include <math.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_774654;
extern int d2_CurrentElementId;
extern int g_14ce8e0;


int __cdecl fcn_004f39b0(int a);
int __cdecl fcn_004f5dd0(int a);
void __cdecl fcn_004f5e20(int a, int b);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_HasActiveSpecialObject(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(char*, int, int);
int __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_RequestMoveCredits(int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl he_NotifyAblassPurchase(char*, char*, char*, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00471e30(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_0050e600(int, int);
void __cdecl fcn_00532ef0(void);
void __cdecl d2_ShowKircheTop5(void);

/* Church indulgence ("Ablass") dialog: offers the indulgence for the current
 * player and, once bought, continues with the results screen. */
/* ADDRESS: GOLDTL 0x005ab3e0 */
void __cdecl fcn_005ab3e0(char* churchBuilding)
{
	char text[0x200];
	char* rec;
	int count;
	int kind;
	int cost;
	int dlg;
	int item;
	int sel;
	int val;
	int changed;
	float scale;
	float factor;
	double scaledPrice;

	item = -1;
	cost = 0;
	count = fcn_004f39b0(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970] + 4));
	kind = fcn_004f5dd0(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970] + 4));
	if (kind != 0) {
		scale = (float) gm_WalkEntityChain(g_774970) * 0.005f;
		factor = 1.5f;
		if (*(unsigned short*) (churchBuilding + 0x27) != g_774970)
			factor = (200.0f - fcn_0050f980(g_774970, *(unsigned short*) (churchBuilding + 0x27), 1)) * 0.01f;
		cost = (int) ((float) kind * factor * scale);
		scaledPrice = (double) cost * 0.1;
		cost = (int) (320000.0 < (scaledPrice > 3200.0 ? scaledPrice : 3200.0) ? 320000.0 : (scaledPrice > 3200.0 ? scaledPrice : 3200.0));
		if (gm_HasActiveSpecialObject((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 0x2c6) != 0)
			cost = cost / 2;
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6ab014);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1960);
	if (cost > 0) {
		io_AppendText(0x1962, count, cost);
		d2_SetForm(dlg, 2);
		item = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1963));
	} else {
		io_AppendText(0x1961, g_774970);
	}
	g_100f1dc = -1;
	changed = 0;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1 && d2_CurrentElementId == item
			&& gm_CheckEntityStock((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], cost, g_773d75) != 0) {
			rec = (char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970];
			cm_BeginPacketFieldDelta(rec, *(int*) (rec + 4));
			cm_AppendPacketFieldValue(4, 1, 0x1ac, &cost);
			cm_RequestChangeAttribute();
			fcn_004f5e20(*(int*) (rec + 4), count);
			if (*(unsigned short*) (churchBuilding + 0x27) != 0xffff
				&& *(unsigned short*) (churchBuilding + 0x27) != g_774970) {
				val = (int) (cost / log10((double) cost));
				cm_RequestMoveCredits(-1, *(int*) (rec + 4), g_773d75, cost);
				sel = cm_RequestMoveCredits(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)(churchBuilding + 0x27)] + 4),
					-1, g_773d75, val);
				he_NotifyAblassPurchase(rec, (char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)(churchBuilding + 0x27)], churchBuilding, val, cost);
			} else {
				sel = cm_RequestMoveCredits(-1, *(int*) (rec + 4), g_773d75, cost);
			}
			while (sel != -1 && cm_GetCommandStatus(sel) == 0)
				fcn_00535960();
			io_FormatTextBuffer(text, 0x1964, *(int*) (rec + 0x1ac), fcn_0050e600(g_774970, 0));
			fcn_00526120(text, 0x100);
			changed = 1;
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) fcn_005ab3e0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	if (changed)
		d2_ShowKircheTop5();
	else
		fcn_00532ef0();
}
