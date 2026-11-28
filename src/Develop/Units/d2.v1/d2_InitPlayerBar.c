

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"









// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x1d0 - 0x60];
	int f1d0;
	char pad1d4[0x1f0 - 0x1d4];
	int owner;
	char pad1f4[0x2f4 - 0x1f4];
} Ent;

// SIZE 0x28
typedef struct {
	int a;
	int pad4;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	char pad20[8];
} Row;

// SIZE 0x21c
typedef struct {
	char pad0[0x164];
	char group;
	char pad165[0x188 - 0x165];
	char marked;
	char pad189[0x21c - 0x189];
} Obj;

extern int g_6a25b4;
extern int g_6a25b8;
extern char g_774724;
extern unsigned char g_77534c;
extern int g_1040494;
extern char g_6a2e94[];
extern char g_6a2ea8[];
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern char* d2_Controls;
extern Row g_7e30c0[32];
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
int __cdecl d2_GetWindowListItem(int h, int a, int b);
void __cdecl d2_SetFormVisibility(int h, int v);
int __cdecl d2_AddWindowImage(int a, int b, int c, int d, int e);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_InitPlayerBar(int unused, char arg)
{
	int owner;
	int id;
	int i;

	if (g_6a25b4 == -1) {
		g_774724 = arg;
		if ((*(char*)&g_77534c) == 0) {
			g_6a25b4 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2ea8);
		} else {
			g_6a25b4 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2e94);
		}
		d2_SetForm(g_6a25b4, 1);
		owner = d2_CurrentWindowId;
		d2_SetForm(g_6a25b4, 2);
		id = d2_GetWindowListItem(g_6a25b4, 2, 0);
		((D2_CONTROL_TL*) d2_Controls)[id].flags_1d0 = 3;
		*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8[0x10] = id;
		((D2_CONTROL_TL*) d2_Controls)[id].value_1f0 = owner;
		id = d2_GetWindowListItem(g_6a25b4, 2, 1);
		((D2_CONTROL_TL*) d2_Controls)[id].flags_1d0 = 3;
		*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8[0x14] = id;
		((D2_CONTROL_TL*) d2_Controls)[id].value_1f0 = owner;
		*(int*) &((D2_WIN*)d2_Windows)[owner].pad3c[0x238] = 0x4e;
		if (g_6a25b4 != -1) {
			if (g_6a25b8 != -1) {
				d2_SetFormVisibility(g_6a25b8, 0);
			}
			d2_SetForm(g_6a25b4, 1);
			for (i = 0; i < 32; i++) {
				g_7e30c0[i].a = -1;
				g_7e30c0[i].b = -1;
				g_7e30c0[i].c = -1;
				g_7e30c0[i].d = 0xffff;
				g_7e30c0[i].e = -1;
				g_7e30c0[i].f = -1;
				g_7e30c0[i].g = 0;
			}
			d2_SetForm(g_6a25b4, 2);
			id = d2_AddWindowImage(0x11, 4, 0x51d, d2_CurrentWindowId, -2);
			((D2_CONTROL_TL*) d2_Controls)[id].value_05c = 1;
			((D2_CONTROL_TL*) d2_Controls)[id].flags_1d0 = 3;
			for (i = 0; i < 768; i++) {
				if ((*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected) != 0 && (*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].stat_category) != 0) {
					(*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected) = 0;
				}
			}
		}
	}
}
