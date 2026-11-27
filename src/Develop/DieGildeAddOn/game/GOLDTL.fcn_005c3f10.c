#include <string.h>
#pragma intrinsic(memset)
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* Entity action dialog for one entity record. Opens the panel, rebuilds its
 * controls while the record or the hovered slot changes, dispatches the
 * dialog message ids, then runs the close/cleanup sequence.
 * ent is the entity record: kind byte at +0, action id at +1, short at
 * +0x25 and +0x27, flags at +0x5a/+0x5b, side byte at +0x5c, byte at
 * +0x65, int at +0x69. */
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct {
	int len;
	int other;
	int h18;
	int h1c;
	int h20;
	int mode;
	int h28;
	char* rec;
	int h30;
	int h34;
	int h38;
	int h3c;
	int ptr;
	int h44;
	int h48;
	int h4c;
	int hover;
	int h54;
	int h58;
	int h5c;
	int prev;
	int id;
} Vars;

/* Dialog message packet, SIZE 0xf8. */
typedef struct {
	char f0[4];
	char f04;
	char f05[3];
	int f08;
	int f0c;
	char f10[0x18];
	int f28;
	int f2c;
	int f30;
	unsigned short f34;
	char f36;
	char f37[0x21];
	int f58;
	char f5c[0x9c];
} Msg;

extern unsigned char* lpGebaeudePROT;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_774654;
extern int d2_CurrentElementId;
extern signed char g_7747b0;
extern unsigned char g_773d75;
extern int g_14ab294;
extern int g_774800;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int tp_d2_SelectedControl;
extern int gm_CityEntity;
extern int g_aed32c;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_662a3c;
extern float g_665c0c;
extern double g_662908;

int __cdecl d2_TutorialAllowsFlag(int a);
void __cdecl fcn_0057e880(int a, int b, int c, int d);
int __cdecl fcn_00504bd0(int a);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl gm_CalculateGebaeudeValue(char* ent, int kind);
int __cdecl gm_CanBuildBuildingType(int a, int b);
int __cdecl he_StartHandlungSearch(int a, int b, int c);
int __cdecl fcn_005462a0(void);
void* __cdecl gm_SearchTable67(int a);
int __cdecl gm_GetEntityMood(char* ent);
void __cdecl fcn_004727a0(int a, int b);
int __cdecl fcn_00519190(int id, ...);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl fcn_00526120(char* text, int mode);
int __cdecl d2_GetWindowListItem(int dlg, int a, int b);
void __cdecl d2_SetElementEnabled(int a, int b);
void __cdecl d2_SetBildArgument(int a, int b);
void __cdecl d2_SetFormVisibility(int a, int b);
void __cdecl d2_DestroyForm(int a);
int __cdecl d2_GetControlValue(int a);
void __cdecl cm_BeginPacketFieldDelta(char* ent, int id);
void __cdecl cm_AppendCommandSyncField(int a, int b, int c, void* d);
void __cdecl cm_RequestMoveCredits(int a, int b, int c, int d);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_SendSetAttribute(void);
void __cdecl cm_SendCopyEntityData(void* msg);
void __cdecl cm_SendSetGebBesitzer(int a, int b, int c);
void __cdecl cm_RequestSetWohnsitz(int a, int b);
void __cdecl gm_BuyBuilding(int a, int b, int c, int d, int e);
int __cdecl fcn_0050d2a0(char* a);
void __cdecl d2_RunTechTreeDialog(int a, int b);
void __cdecl d2_ShowSellGebaeudeDialog(int a);
void __cdecl d2_ShowRenovationDialog(int a);
void __cdecl d2_ShowGebaeudeSaleDialog(int a);
void __cdecl d2_RunRoomUpgradeDialog(int a);
void __cdecl d2_RunBuildingUpgradeDialog(int a);
void __cdecl d2_RunSellGebaeudeDialog(int a);
void __cdecl d2_ShowTechTreeEffects(int a);
void __cdecl d2_RunFireExtinguishDialog(int a);
int __cdecl main_RunFrameLoop(void* fn, int message);

/* ADDRESS: GOLDTL 0x005c3f10 */
void __cdecl d2_RunGebaeudeOptionenDialog(char* ent)
{
	Vars v;
	Msg st;
	char name[0x80];
	char text1[0x200];
	char text2[0x200];
	char text3[0x400];
	char* s;
	char* d;
	char c;
	int changed;
	int dlg;
	int h;
	int n2;

	v.prev = -1;
	v.h34 = -1;
	v.h3c = -1;
	v.h1c = -1;
	v.h30 = -1;
	v.h54 = -1;
	v.h44 = -1;
	v.h20 = -1;
	v.h4c = -1;
	v.h28 = -1;
	v.h18 = -1;
	v.h38 = -1;
	v.h5c = -1;
	v.h48 = -1;
	v.h58 = -1;
	changed = 1;
	v.rec = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char)ent[0]];
	v.other = 0;
	v.hover = 0;
	v.id = *(int*) (ent + 1);
	if ((*(unsigned short*) (ent + 0x5a) & 0x400) != 0)
		return;
	if (*(unsigned short*) (ent + 0x25) == g_774970) {
		if (d2_TutorialAllowsFlag(0x100) == 0)
			return;
		if (*(unsigned short*) (ent + 0x25) == g_774970)
			fcn_0057e880(0x10, (int) ent, 0, 0);
	} else {
		if (d2_TutorialAllowsFlag(0x4000) == 0)
			return;
	}
	v.mode = fcn_00504bd0((unsigned char) ent[0]);
	dlg = fcn_00470820(0, 0, (char*) 0x6ac690);
	d2_CenterDialogWindows(dlg);
	fcn_00473a90(0, 0);
	v.ptr = gm_CalculateGebaeudeValue(ent, ent[0x5c]);
	gm_CanBuildBuildingType((unsigned char) ent[0], g_774970);
	if ((*(unsigned char*) (ent + 0x5a) & 2) != 0
	    && *(unsigned short*) (ent + 0x25) != g_774970) {
		v.other = he_StartHandlungSearch(1, 0, 0x1b);
		while (v.other != 0
		    && *(int*) (ent + 1) != *(int*) (v.other + 0xac))
			v.other = fcn_005462a0();
	}
	do {
		if ((*(unsigned char*) (ent + 0x5b) & 4) != 0
		    || gm_SearchTable67(v.id) == 0)
			g_774654 = 1;
		if (*(unsigned short*) (ent + 0x5a) != v.prev)
			changed = 1;
		if (*(unsigned short*) (ent + 0x27) == g_774970) {
			h = he_StartHandlungSearch(1, 0, 0x4f);
			while (h != 0
			    && *(int*) (h + 0xac) != *(int*) (ent + 1))
				h = fcn_005462a0();
			if (h != v.hover) {
				changed = 1;
				v.hover = h;
			}
		}
		v.prev = *(unsigned short*) (ent + 0x5a);
		if (changed) {
			v.h34 = -1;
			v.h3c = -1;
			v.h1c = -1;
			v.h30 = -1;
			v.h54 = -1;
			v.h44 = -1;
			v.h20 = -1;
			v.h4c = -1;
			v.h28 = -1;
			v.h18 = -1;
			v.h38 = -1;
			v.h48 = -1;
			v.h58 = -1;
			fcn_004727a0(dlg, 1);
			v.len = gm_GetEntityMood(ent);
			if (*(unsigned short*) (ent + 0x27) == g_774970) {
				if (*(unsigned short*) (ent + 0x25) == g_774970)
					goto build_other;
				if (*(unsigned short*) (ent + 0x27) != g_774970)
					goto after_build;
			} else if (*(unsigned short*) (ent + 0x25)
			    == g_774970) {
				goto build_other;
			}
			n2 = (int) ((double) v.len * g_662a3c
			    - g_665c0c + 0.5);
			fcn_00519190(
			    (v.rec[0] == 0x21) ? 0x17fb : 0x17a0,
			    (unsigned short) *(unsigned short*) (ent + 0x25),
			    (int) ent, n2 + 0x17b1, n2 + 0x17bb, v.ptr);
			if (v.rec[0] == 1)
				fcn_00519190(0x17a2,
				    (unsigned char) ent[0x65]);
			if (v.mode != 3 && v.mode != 5 && v.rec[0] != 1) {
				if (v.other != 0)
					v.h54 = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17aa));
				else if (v.mode != 2 || v.rec[0] == 0x10)
					v.h20 = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17ad));
				if ((*(unsigned char*) (ent + 0x5b) & 2) != 0)
					d2_SetElementEnabled(v.h20, 0);
			}
			goto after_build;
build_other:
			n2 = (int) ((double) v.len * g_662a3c
			    - g_665c0c + 0.5);
			fcn_00519190(
			    (v.rec[0] == 0x21) ? 0x17f9 : 0x179e,
			    (int) ent, n2 + 0x17b1, n2 + 0x17bb, v.ptr);
			if (*(unsigned short*) (ent + 0x25) == g_774970) {
				if (v.rec[0] == 0x21)
					v.h38 = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17fc, ent + 5));
				else
					v.h38 = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17a1, ent + 5));
				d2_SetBildArgument(v.h38, 0x10);
			}
			if (v.rec[0] == 1)
				fcn_00519190(0x17a2,
				    (unsigned char) ent[0x65]);
			if (v.mode == 2) {
				v.h48 = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x17af));
			} else {
				if ((*(unsigned char*) (ent + 0x5a) & 2)
				    != 0)
					v.h44 = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17a7));
				else
					v.h1c = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17a4));
			}
			v.h3c = d2_GetWindowListItem(dlg, 1,
			    fcn_00519190(0x17a5));
			if ((*(unsigned char*) (ent + 0x5a) & 0x18) == 0
			    && v.mode != 2 && v.rec[0] != 0x10)
				v.h30 = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x17a6));
			if (v.rec[0] != 3 && v.rec[0] != 0x21)
				v.h34 = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x17ac));
			if ((unsigned char) v.rec[0x21] > 1)
				v.h28 = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x17a8));
			else
				v.h28 = -1;
			if (v.mode != 2)
				v.h18 = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x17ab));
			if (v.hover != 0)
				v.h58 = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x17b0));
			if (*(unsigned short*) (ent + 0x27) == g_774970) {
				fcn_004727a0(dlg, 1);
				if (v.rec[0] == 2
				    && *(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]

					+ 0x170) != (int) ent)
					v.h4c = d2_GetWindowListItem(dlg, 1,
					    fcn_00519190(0x17a9));
			}
after_build:
			if (g_774800 != 0)
				v.h5c = d2_GetWindowListItem(dlg, 1,
				    fcn_00519190(0x1ba7));
			changed = 0;
		}
		if ((*(unsigned char*) (ent + 0x5a) & 4) != 0) {
			d2_SetElementEnabled(v.h34, 0);
			d2_SetElementEnabled(v.h3c, 0);
			d2_SetElementEnabled(v.h30, 0);
			d2_SetElementEnabled(v.h1c, 0);
		}
		if (v.h18 != -1) {
			if ((*(unsigned char*) (ent + 0x5a) & 0x40) != 0)
				d2_SetElementEnabled(v.h18, 0);
			else
				d2_SetElementEnabled(v.h18, 1);
		}
		if (g_14ce8e0 != 0 && tp_d2_SelectedControl == 0)
			g_774654 = 1;
		if (g_100f1dc == -1)
			goto loop_test;
		if (d2_CurrentElementId == v.h34) {
			d2_SetFormVisibility(dlg, 0);
			d2_RunTechTreeDialog((int) ent, 0xfd);
			d2_SetFormVisibility(dlg, 1);
			goto loop_test;
		}
		if (d2_CurrentElementId == v.h1c && g_7747b0 >= 0) {
			d2_SetFormVisibility(dlg, 0);
			d2_ShowSellGebaeudeDialog((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h3c && g_7747b0 >= 0) {
			d2_SetFormVisibility(dlg, 0);
			d2_ShowRenovationDialog((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h20 && g_7747b0 >= 0) {
			d2_SetFormVisibility(dlg, 0);
			d2_RunSellGebaeudeDialog((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h44 && g_7747b0 >= 0) {
			d2_SetFormVisibility(dlg, 0);
			d2_ShowGebaeudeSaleDialog((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h28 && g_7747b0 >= 0) {
			d2_SetFormVisibility(dlg, 0);
			d2_RunRoomUpgradeDialog((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h4c) {
			d2_SetFormVisibility(dlg, 0);
			cm_RequestSetWohnsitz(
			    *(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]
 + 4),
			    *(int*) (ent + 1));
			d2_SetFormVisibility(dlg, 1);
			goto tail_changed;
		}
		if (d2_CurrentElementId == v.h18 && g_7747b0 >= 0) {
			d2_SetFormVisibility(dlg, 0);
			d2_RunBuildingUpgradeDialog((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h30 && g_7747b0 >= 0) {
			io_FormatTextBuffer(text1, 0x17c7, (int) ent);
			d2_SetFormVisibility(dlg, 0);
			if (fcn_00526120(text1, 1) != 0) {
				memset(&st, 0, sizeof(st));
				st.f04 = 0x20;
				st.f08 = *(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]
 + 4);
				st.f0c = *(int*) (ent + 1);
				st.f28 = gm_GameTime;
				st.f2c = g_7f4c04;
				st.f30 = g_7f4c08;
				st.f34 = g_7f4c0c;
				st.f36 = 1;
				st.f58 = *(int*) (ent + 1);
				cm_SendCopyEntityData(&st);
				g_774654 = 1;
			}
			d2_SetFormVisibility(dlg, 1);
			goto tail_changed;
		}
		if (d2_CurrentElementId == v.h54 && g_7747b0 >= 0) {
			if (gm_CanBuildBuildingType((unsigned char) ent[0],
				g_774970) != 1) {
				fcn_00526120((char*) g_14ab294, 0);
				goto loop_test;
			}
			d2_SetFormVisibility(dlg, 0);
			if (fcn_0050d2a0((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]
)
			    > *(int*) (v.other + 0xb0)) {
				io_FormatTextBuffer(text2, 0x17db,
				    (unsigned short) *(unsigned short*)
					(ent + 0x25), (int) ent,
				    *(int*) (v.other + 0xb0));
				if (fcn_00526120(text2, 1) != 0) {
					gm_BuyBuilding(*(int*) (ent + 1),
					    *(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]

 + 4),
					    *(int*) (v.other + 0xb0),
					    v.other, 0);
				}
			}
			d2_SetFormVisibility(dlg, 1);
			goto tail_changed;
		}
		if (d2_CurrentElementId == -1) {
			d2_SetFormVisibility(dlg, 0);
			d2_ShowTechTreeEffects((int) ent);
			goto tail_on;
		}
		if (d2_CurrentElementId == v.h5c) {
			cm_SendSetGebBesitzer(*(int*) (ent + 1),
			    *(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]
 + 4),
			    *(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]
 + 4));
			goto tail_changed;
		}
		if (d2_CurrentElementId == v.h48) {
			v.len = *(int*) (ent + 0x69)
			    + *(int*) (ent + 0x65);
			d2_SetFormVisibility(dlg, 0);
			v.len = (int) ((double) v.len * 0.5);
			io_FormatTextBuffer(text3, 0x17e3, (int) ent,
			    (int) ent, v.len);
			if (fcn_00526120(text3, 1) != 0) {
				cm_RequestMoveCredits(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)g_774970]

					+ 4), -1, g_773d75, v.len);
				cm_SendSetGebBesitzer(*(int*) (ent + 1),
				    *(int*) (gm_CityEntity + 4),
				    *(int*) (gm_CityEntity + 4));
				cm_BeginPacketFieldDelta(ent, *(int*) (ent + 1));
				cm_AppendCommandSyncField(4, 1,
				    (int) ent - g_aed32c + 0x65, &v.len);
				cm_RequestChangeAttribute();
				g_774654 = 1;
			}
			d2_SetFormVisibility(dlg, 1);
			goto tail_changed;
		}
		if (d2_CurrentElementId == v.h58) {
			d2_SetFormVisibility(dlg, 0);
			d2_RunFireExtinguishDialog((int) ent);
			goto tail_on;
		}
		goto loop_test;
tail_on:
		d2_SetFormVisibility(dlg, 1);
tail_changed:
		changed = 1;
loop_test:
		;
	} while (main_RunFrameLoop((void*) 0x5c3f10, 0x657c7) != 0);

	if (v.h38 != -1) {
		s = (char*) d2_GetControlValue(v.h38);
		d = name;
		do {
			c = *s++;
			*d++ = c;
		} while (c != 0);
		cm_BeginPacketFieldDelta(ent, *(int*) (ent + 1));
		cm_AppendCommandSyncField(1, 0x20, 5, name);
		cm_SendSetAttribute();
	}
	d2_DestroyForm(dlg);
	if (*(unsigned short*) (ent + 0x25) == g_774970)
		fcn_0057e880(0x10, (int) ent, 1, 0);
}
