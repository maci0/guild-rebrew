#include "client_dialog_helpers.h"
#include "client_actions.h"
#include "client_types.h"
typedef struct { unsigned char kind, unknown01[0x24c]; } BuildingProto599b00;
typedef struct {
    char unknown00[4]; unsigned char kind; char unknown05[3];
    int actor, target; char unknown10[0x18]; pos14_7f4c00 pos;
    unsigned char mode; char unknown37[0x21];
    int owner, category, cost; char unknown64[0x1c];
    float location[3]; char unknown8c[4]; float rotation[3];
    char name[0x3f], unknowndb[0x1d];
} BuildingMsg599b00;
extern int gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"

/* City construction dialog ("BAUEN\\STADT_BAUEN"). Builds the category
 * list, keeps one hotkey row per building category, then runs the message
 * loop that reacts to the chosen building and to the close messages. */

#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_7746f8;
#include "client_dialog_state.h"
extern char* g_1015ea0;
extern int g_10162e8;
extern int g_10162ec;
extern int g_10162f0;
extern int g_10162f4;
extern unsigned char g_773d75;
extern int g_68a2a8;
extern int g_6b5c60;
extern int d2_CurrentElementId;


int __cdecl gm_GetGuildHall(int a);
int __cdecl fcn_00502cd0(int, int, ...);
void __cdecl d2_CenterDialogWindows(int dlg);
int __cdecl gm_CalcBuildingCost(int a, int b);
int __cdecl d2_AddElementToWindow(int a, int b, int c, int d);
int __cdecl fcn_0046fac0(int a, int b, int c, int d);
void __cdecl d2_SetElementFont(int a, int b);
void __cdecl fcn_0046f940(int a, int b);
int __cdecl d2_CheckFundsAndNotify(int, int, int, int);
int __cdecl lc_GebaeudeAusrichten(int, char*);
void __cdecl d3_TransformPoint(int a, int b, void* c);
void __cdecl d3_ComputeObjectYawToTarget(void* a, int b);
void __cdecl cm_SendCopyEntityData(void* a);
void __cdecl fcn_0050bc10(int a, unsigned char b, char* c);
void __cdecl d2_ScrollWindow(int a, int b, int c);
int __cdecl main_RunFrameLoop(int a, int b);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00599b00 */
void __cdecl fcn_00599b00(void)
{
	int cats[5];
	unsigned char* catp;
	char name[260];
	char key[128];
	BuildingMsg599b00 msg;
	int query, cost, selected;
	int raw;
	int dlg;
	int i;
	int row;
	int ofs;
	int cat;
	int last;
	int ent;
	BuildingProto599b00* rec;
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
	dlg = fcn_00470820(0, 0, (char*) 0x6aa2a8);
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
		rec = &((BuildingProto599b00*)lpGebaeudePROT)[cat];
		kind = rec->kind;
		if (kind != last && last != -1) {
			row += 0x50;
			ofs = 0;
		}
		cost = gm_CalcBuildingCost((int)&((ENTITY_RECORD*)g_7f4ca0)[
		    (unsigned short)g_774970], cat);
		last = rec->kind;
		raw = d2_AddElementToWindow(ofs + 0x30, row - 0x30, cat + 0x427,
		    d2_CurrentWindowId);
		/* raw is the control index. */
		((D2_CONTROL_TL*)g_1015ea0)[raw].value_05c = 1;
		((D2_CONTROL_TL*)g_1015ea0)[raw].flags_1d0 = 3;
		src = *(char**) (cat * 0x38 + 0x14a6558);
		dst = (char*) ((char*) &((D2_CONTROL_TL*)g_1015ea0)[raw] + 0xcc);
		do {
			c = *src++;
			*dst++ = c;
		} while (c != 0);
		((D2_CONTROL_TL*)g_1015ea0)[raw].value_1cc = 0x54;
		fcn_0050bc10(cost, g_773d75, key);
		ent = fcn_0046fac0(ofs + 2, row, 0x6b5c60, d2_CurrentWindowId);
		d2_SetElementFont(ent, 0x54);
		fcn_0046f940(ent, key);
		ofs += 0x60;
		((D2_CONTROL_TL*) (g_1015ea0))[ent].width = 0x8c;
		((D2_CONTROL_TL*) (g_1015ea0))[ent].value_06c = 1;
	}
	for (;;) {
		if (g_100f1dc >= 0x427 && g_100f1dc <= 0x47f) {
			i = g_100f1dc - 0x427;
			if (selected != -1) {
				((D2_CONTROL_TL*) (g_1015ea0))[selected].value_038 = 0;
				((D2_CONTROL_TL*) (g_1015ea0))[selected].value_03c = 0;
			}
			selected = d2_CurrentElementId;
			ent = d2_CheckFundsAndNotify(query, *(int*) (query + 0x14),
			    gm_CalcBuildingCost((int)((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]), i), g_773d75);
			if (ent != 0) {
				d2_SetFormVisibility(dlg, 0);
				ent = lc_GebaeudeAusrichten(i, name);
				if (ent != 0) {
					msg.kind = 0x0d;
					msg.mode = 2;
					msg.actor = *(int*)((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970] + 4);
					msg.target = msg.actor;
					msg.pos.a = gm_GameTime;
					msg.pos.b = g_7f4c04;
					msg.pos.c = g_7f4c08;
					msg.pos.d = g_7f4c0c;
					msg.owner = *(int*)(gm_CityEntity + 4);
					msg.category = i;
					msg.cost = gm_CalcBuildingCost((int)((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]), i);
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
					g_774654 = 1;
				} else {
					d2_SetFormVisibility(dlg, 1);
				}
			}
		}
		if (g_100f1dc == 3) {
			d2_SetForm(dlg, 3);
			d2_ScrollWindow(0, -0x46, d2_CurrentWindowId);
		} else if (g_100f1dc == 4) {
			d2_SetForm(dlg, 3);
			d2_ScrollWindow(0, 0x46, d2_CurrentWindowId);
		}
		if (g_14ce8e0 != 0)
			g_774654 = 1;
		if (main_RunFrameLoop(0x599b00, 0x657c7) == 0) {
			if (dlg != -1)
				d2_DestroyForm(dlg);
			g_7746f8 = 0;
			return;
		}
	}
}
