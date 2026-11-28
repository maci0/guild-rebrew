

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x2f4 - 0x60];
} Ent;

extern int g_6a25b8;
extern int g_1040494;
extern char g_6a2f40[];
extern char g_6a2f64[];
extern char g_6a2f24[];
extern char g_6a2f5c[];
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14ad0d8;
extern int g_14ad0dc;
extern int g_6a25e0;
extern int g_6a25ec;

int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_AppendText(char* fmt, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int kind, int owner);
unsigned short* __cdecl gm_ResolveParentEntity(unsigned short* e);
int __cdecl gm_GetEntityUiFlags(int id, unsigned char* store, int a, int b);
int __cdecl gm_CollectBuildingSubObjects(unsigned char* store, unsigned short* item, int a);
int __cdecl d2_CreateWindowTextButton(int x, int y, int z);

void __cdecl d2_ShowGebaeudeItemInfoPanel(unsigned short* item)
{
	unsigned char* store;
	unsigned short* parent;
	char* rec;
	int id;
	int fl;

	store = 0;
	if (g_6a25b8 != -1) {
		return;
	}
	if (*item >= 0x92 && *item <= 0x97) {
		return;
	}
	if (*item == 0x2db) {
		return;
	}
	g_6a25b8 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2f40);
	d2_SetForm(g_6a25b8, 1);
	if (((unsigned char*)d2_VisitedBuilding) != 0 || d2_InteriorBuilding != 0) {
		store = ((unsigned char*)d2_VisitedBuilding) != 0 ? ((unsigned char*)d2_VisitedBuilding) : d2_InteriorBuilding;
	}
	if (store != 0) {
		if (store[5] != 0) {
			io_AppendText(g_6a2f64, *store * 14 + 0x48e, store + 5, *item * 2 + 0x9a8);
		} else {
			io_AppendText(g_6a2f24, *store * 14 + 0x48e, *item * 2 + 0x9a8);
		}
	} else {
		io_AppendText(g_6a2f5c, *item * 2 + 0x9a8);
	}
	d2_SetForm(g_6a25b8, 0);
	id = d2_AddElementToWindow(((((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) - 1, 0x48, *item + 0xdf, d2_CurrentWindowId);
	((D2_CONTROL_TL*)d2_Controls)[id].value_05c = 1;
	rec = (char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[*item];
	if (store != 0 && (*rec == 2 || *rec == 6)) {
		parent = gm_ResolveParentEntity(item);
		fl = gm_GetEntityUiFlags(gm_LocalPlayerSlot, store, 0, 0);
		if (*parent != gm_LocalPlayerSlot && !(fl & 0x10)) {
			g_6a25e0 = d2_CreateWindowTextButton(0, 0xa6, g_14ad0dc);
		} else {
			if (gm_CollectBuildingSubObjects(store, item, 0)) {
				g_6a25ec = d2_CreateWindowTextButton(0, 0x8c, g_14ad0d8);
			}
			g_6a25e0 = d2_CreateWindowTextButton(0, 0xa6, g_14ad0dc);
		}
	}
}
