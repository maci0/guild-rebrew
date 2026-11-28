#include "Develop/Units/d2.v1/client_dialog_helpers.h"
#include "Develop/DieGildeAddOn/game/client_actions.h"
#include "Develop/client_types.h"
typedef struct { unsigned char kind, unknown01[0x24c]; } D2_STADT_BAUEN_PROTO;
typedef struct {
    char unknown00[4]; unsigned char kind; char unknown05[3];
    int actor, target; char unknown10[0x18]; pos14_7f4c00 pos;
    unsigned char mode; char unknown37[0x21];
    int owner, category, cost; char unknown64[0x1c];
    float location[3]; char unknown8c[4]; float rotation[3];
    char name[0x3f], unknowndb[0x1d];
} D2_STADT_BAUEN_MSG;
extern int gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"

/* City construction dialog ("BAUEN\\STADT_BAUEN"). Builds the category
 * list, keeps one hotkey row per building category, then runs the message
 * loop that reacts to the chosen building and to the close messages. */

#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int g_7746f8;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char* d2_Controls;
extern int g_10162e8;
extern int g_10162ec;
extern int g_10162f0;
extern int g_10162f4;
extern unsigned char gm_ActiveTownIndex;
extern int g_68a2a8;
extern int str_empty;
extern int d2_CurrentElementId;


int __cdecl gm_GetGuildHall(int a);
int __cdecl fcn_00502cd0(int, int, ...);
void __cdecl d2_CenterDialogWindows(int dlg);
int __cdecl gm_CalcBuildingCost(int a, int b);
int __cdecl d2_AddElementToWindow(int a, int b, int c, int d);
int __cdecl d2_EqualizeWindowButtonWidths(int a, int b, int c, int d);
void __cdecl d2_SetElementFont(int a, int b);
void __cdecl d2_SetLabelText(int a, int b);
int __cdecl d2_CheckFundsAndNotify(int, int, int, int);
int __cdecl lc_GebaeudeAusrichten(int, char*);
void __cdecl d3_TransformPoint(int a, int b, void* c);
void __cdecl d3_ComputeObjectYawToTarget(void* a, int b);
void __cdecl cm_SendCopyEntityData(void* a);
void __cdecl d2_FormatCurrencyString(int a, unsigned char b, char* c);
void __cdecl d2_ScrollWindow(int a, int b, int c);
int __cdecl main_RunFrameLoop(int a, int b);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00599b00 */
void __cdecl d2_RunStadtBauenDialog(void)
{
	int cats[5];
	unsigned char* catp;
	char name[260];
	char key[128];
	D2_STADT_BAUEN_MSG msg;
	int query, cost, selected;
	int raw;
	int dlg;
	int i;
	int row;
	int ofs;
	int cat;
	int last;
	int ent;
	D2_STADT_BAUEN_PROTO* rec;
	unsigned char kind;
	char* src;
	char* dst;
	char c;

	last = -1;
	selected = -1;
	cats[0] = 8;
	cats[1] = 9;
	cats[2] = 10;
	cats[3] = 1;
	cats[4] = 0;
	raw = gm_GetGuildHall(1);
	raw = *(int*) (raw + 0x5d);
	query = fcn_00502cd0(raw, 2, 6, 0, 0x115);
	dlg = d2_LoadForm(0, 0, (char*) 0x6aa2a8);
	d2_CenterDialogWindows(dlg);
	g_7746f8 = 1;
	d2_SetForm(dlg, 0);
	i = d2_CurrentWindowId * 0x3cc;
	*(int*) (i + 0x10162e8) = 0x18;
	*(int*) (i + 0x10162ec) = 0x18;
	*(int*) (i + 0x10162f0) = 0x18;
	*(int*) (i + 0x10162f4) = 0x18;
	d2_SetForm(dlg, 1);
	io_AppendText((void*) 0x17f3);
	d2_SetForm(dlg, 2);
	ofs = 0;
	row = 0x40;
	for (i = 0; cats[i] != 0; i++) {
		cat = cats[i];
		rec = &((D2_STADT_BAUEN_PROTO*)lpGebaeudePROT)[cat];
		kind = rec->kind;
		if (kind != last && last != -1) {
			row += 0x50;
			ofs = 0;
		}
		cost = gm_CalcBuildingCost((int)&((ENTITY_RECORD*)gm_EntitySlotTable)[
		    (unsigned short)gm_LocalPlayerSlot], cat);
		last = rec->kind;
		raw = d2_AddElementToWindow(ofs + 0x30, row - 0x30, cat + 0x427,
		    d2_CurrentWindowId);
		/* raw is the control index. */
		((D2_CONTROL_TL*)d2_Controls)[raw].value_05c = 1;
		((D2_CONTROL_TL*)d2_Controls)[raw].flags_1d0 = 3;
		src = *(char**) (cat * 0x38 + 0x14a6558);
		dst = (char*) ((char*) &((D2_CONTROL_TL*)d2_Controls)[raw] + 0xcc);
		do {
			c = *src++;
			*dst++ = c;
		} while (c != 0);
		((D2_CONTROL_TL*)d2_Controls)[raw].value_1cc = 0x54;
		d2_FormatCurrencyString(cost, gm_ActiveTownIndex, key);
		ent = d2_EqualizeWindowButtonWidths(ofs + 2, row, 0x6b5c60, d2_CurrentWindowId);
		d2_SetElementFont(ent, 0x54);
		d2_SetLabelText(ent, key);
		ofs += 0x60;
		((D2_CONTROL_TL*) (d2_Controls))[ent].width = 0x8c;
		((D2_CONTROL_TL*) (d2_Controls))[ent].value_06c = 1;
	}
	for (;;) {
		if (d2_DialogButtonAction >= 0x427 && d2_DialogButtonAction <= 0x47f) {
			i = d2_DialogButtonAction - 0x427;
			if (selected != -1) {
				((D2_CONTROL_TL*) (d2_Controls))[selected].value_038 = 0;
				((D2_CONTROL_TL*) (d2_Controls))[selected].value_03c = 0;
			}
			selected = d2_CurrentElementId;
			ent = d2_CheckFundsAndNotify(query, *(int*) (query + 0x14),
			    gm_CalcBuildingCost((int)((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), i), gm_ActiveTownIndex);
			if (ent != 0) {
				d2_SetFormVisibility(dlg, 0);
				ent = lc_GebaeudeAusrichten(i, name);
				if (ent != 0) {
					msg.kind = 0x0d;
					msg.mode = 2;
					msg.actor = *(int*)((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot] + 4);
					msg.target = msg.actor;
					msg.pos.a = gm_GameTime;
					msg.pos.b = gm_GameTimeHour;
					msg.pos.c = gm_GameTimeSliceDword;
					msg.pos.d = gm_GameTimeTailWord;
					msg.owner = *(int*)(gm_CityEntity + 4);
					msg.category = i;
					msg.cost = gm_CalcBuildingCost((int)((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), i);
					d3_TransformPoint(ent, ent + 0x4c, msg.location);
					d3_ComputeObjectYawToTarget(msg.rotation, ent);
					{
						int k = 0;
						do {
							c = name[k];
							msg.name[k++] = c;
						} while (c != 0);
					}
					cm_SendCopyEntityData(&msg);
					d2_DialogCloseRequested = 1;
				} else {
					d2_SetFormVisibility(dlg, 1);
				}
			}
		}
		if (d2_DialogButtonAction == 3) {
			d2_SetForm(dlg, 3);
			d2_ScrollWindow(0, -0x46, d2_CurrentWindowId);
		} else if (d2_DialogButtonAction == 4) {
			d2_SetForm(dlg, 3);
			d2_ScrollWindow(0, 0x46, d2_CurrentWindowId);
		}
		if (io_RightButtonReleased != 0)
			d2_DialogCloseRequested = 1;
		if (main_RunFrameLoop(0x599b00, 0x657c7) == 0) {
			if (dlg != -1)
				d2_DestroyForm(dlg);
			g_7746f8 = 0;
			return;
		}
	}
}
