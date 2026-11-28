#include "Develop/DieGildeAddOn/game/object_prototype.h"

#pragma pack(push, 1)
// SIZE 0x61
typedef struct {
	char pad0[0x5d];
	int home;
} Player;

// SIZE 0x41
typedef struct {
	unsigned char type;
	char pad1[0x40];
} Ware;
#pragma pack(pop)

// SIZE 0x18
typedef struct {
	char pad0[0x14];
	int home;
} Estate;

// SIZE 0x1c
typedef struct {
	unsigned short slot;
	char pad2[0x16];
	void* model;
} Unit;

// SIZE 0x8
typedef struct {
	char* name;
	int pad4;
} WareName;

extern char* sv_SelectedBuilding;
extern unsigned char* d2_InteriorBuilding;
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14a79c0[];

void* __cdecl gm_QueryEntities(int, int, int, ...);
void __cdecl d2_SelectFont(int);
char __cdecl d3_GetObjectScreenRect(void*, int*);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);
Unit* __cdecl gm_NextEntityQueryMatch(void);

void __cdecl d2_DrawBuildingItemLabels(void)
{
	int r[4];
	int home;
	Unit* u;
	Estate* e;
	OBJECT_PROTOTYPE* w;

	if (((Estate*)sv_SelectedBuilding) != 0) {
		home = ((Estate*)sv_SelectedBuilding)->home;
	} else {
		if (((Player*)d2_InteriorBuilding) == 0) {
			return;
		}
		e = gm_QueryEntities(((Player*)d2_InteriorBuilding)->home, 1, 0, 0xfd);
		if (e != 0) {
			home = e->home;
		} else {
			home = ((Player*)d2_InteriorBuilding)->home;
		}
	}
	d2_SelectFont(0x54);
	for (u = gm_QueryEntities(home, 1, 5); u != 0; u = gm_NextEntityQueryMatch()) {
		w = &((OBJECT_PROTOTYPE*)lpObjektePROT)[u->slot];
		if (u->model != 0 && w->kind != 6 && w->kind != 2
			&& d3_GetObjectScreenRect(u->model, r)) {
			d2_DrawWordWrappedText((r[2] - r[0]) / 2 + r[0] - 0x50, r[1], 0xa0, 0x60, d2_ScreenSurface,
				((WareName*)g_14a79c0)[u->slot].name, 0x28);
		}
	}
	if (((Estate*)sv_SelectedBuilding) != 0) {
		home = ((Estate*)sv_SelectedBuilding)->home;
	} else if (((Player*)d2_InteriorBuilding) != 0) {
		home = ((Player*)d2_InteriorBuilding)->home;
	}
	for (u = gm_QueryEntities(home, 2, 5, 6); u != 0; u = gm_NextEntityQueryMatch()) {
		w = &((OBJECT_PROTOTYPE*)lpObjektePROT)[u->slot];
		if (u->model != 0 && (w->kind == 6 || w->kind == 2)
			&& d3_GetObjectScreenRect(u->model, r)) {
			d2_DrawWordWrappedText((r[2] - r[0]) / 2 + r[0] - 0x50, r[1], 0xa0, 0x60, d2_ScreenSurface,
				((WareName*)g_14a79c0)[u->slot].name, 0x28);
		}
	}
}
