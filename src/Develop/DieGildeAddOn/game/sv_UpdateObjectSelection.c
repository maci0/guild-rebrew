#include <string.h>

// SIZE 0x2c
typedef struct {
	float ox;
	float oy;
	float oz;
	int pad0c;
	float sx;
	float sy;
	float sz;
	int pad1c;
	int n;
	int* cells;
	unsigned char* data;
} SELECTION_SCENE_MAP;

/* SIZE 0x1c */
typedef struct {
	int id;
	char pad4[0x18];
} SELECTION_MAP_CELL;

/* SIZE 0x21c */
typedef struct {
	unsigned short id;
	short pad2;
	int handle;
	char f8;
	char pad9[0x163];
	int f16c;
	char pad170[0x14];
	char* owner;
	char flag;
	char pad189[3];
	int f18c;
	char pad190[0x8c];
} SELECTION_ENTITY_SLOT;

extern int d3_ActiveScene;
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;
extern char* sv_SelectedBuilding;
extern int sv_ClickedObjekt;
extern int g_7746b8;
extern int d2_SelectedPerson;
extern char sv_EntityGreyTintFlags[];
extern char* ch_ContextCharacters[32];
extern char gm_EntitySlotTable[];
extern int g_7e4318;
extern unsigned short* g_7e431c;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_SetObjectGreyTint(int, int);
void* __cdecl evt_FindScriptById(int);
int __cdecl evt_RequestScriptExit(char*);
int __cdecl d3_FindSceneObject(char*, int, char*, char*);
char __cdecl d3sm_RaycastScreenPoint(int, int, int, int*, int*);
void __cdecl d2_AddDisplayCounter(int, int);
void __cdecl ResetDisplayCounters(void);
void __cdecl d3snd_PlaySelectedObjectClickSound(void);
void __cdecl cm_RequestWalkOnPath(int, int, int, int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl cm_RequestUseGate(int, int, int);
int __cdecl gm_GetEntityUiFlags(int, unsigned char*, unsigned short*, int);
void __cdecl he_AssignActionSlot(int, int, int, int);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl he_RedirectStreifeSelection(void);
int __cdecl init_EnsureObjektSceneContext(char*);
int __cdecl init_AllocateGebaeudeSceneSlot(unsigned char*);
void __cdecl d3_BeginSelectionBox(void);
void __cdecl d3_ClearSelectionBox(void);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x00531620 */
void __cdecl sv_UpdateObjectSelection(void)
{
	SELECTION_SCENE_MAP* map;
	SELECTION_ENTITY_SLOT* s;
	char* ent;
	char* p;
	char* e;
	char* f;
	union {
		char buf[0x80];
		int offs[9][2];
	} u;
	int a;
	int b;
	int ix;
	int iy;
	int k;
	int idx;
	int c;
	int cell;
	int dimension;
	int ei;
	int w;

	ent = 0;
	a = -1;
	b = -1;
	map = *(SELECTION_SCENE_MAP**) ((char*) d3_ActiveScene + 0xb0);
	if (d2_VisitedBuilding != 0) {
		ent = d2_VisitedBuilding;
	} else if (d2_InteriorBuilding != 0) {
		ent = (char*) d2_InteriorBuilding;
	}
	if (g_14ce8d4 != 0) {
		goto L684;
	}
	if (d3_SelectionBoxActive != 0) {
		d3snd_PlaySelectedObjectClickSound();
		d3_ClearSelectionBox();
		if (g_14ce8d4 != 0) {
			goto L684;
		}
	}
	goto L6d3;

L684:
	if (g_14ce8e4 == 0) {
		if (d3_SelectionBoxActive == 0 && g_6772c4 != 0 && d2_HoveredWindow == -1
		    && ent != 0 && *(unsigned short*) (ent + 0x27) == gm_LocalPlayerSlot) {
			d3_BeginSelectionBox();
		}
		goto La5d;
	}

L6d3:
	if (g_7746f0 == 0) {
		goto La5d;
	}
	if (g_7746b8 != 0) {
		goto L192f;
	}
	if (sv_ClickedObjekt != 0) {
		goto La50;
	}
	if ((*(int *)&g_7e431c) != 0) {
		goto La50;
	}
	if (g_7e4318 != 0) {
		he_RedirectStreifeSelection();
		goto La5d;
	}
	if (map == 0 || ent == 0 || g_14ce8cc == 0 || d2_HoveredWindow != -1) {
		goto La5d;
	}
	k = 0;
	for (idx = 0; idx < 0x300; idx++) {
		s = &((SELECTION_ENTITY_SLOT*) gm_EntitySlotTable)[idx];
		if (s->flag == 0) {
			continue;
		}
		if (s->f8 == 0) {
			continue;
		}
		if ((gm_GetEntityUiFlags(gm_LocalPlayerSlot, 0, 0, (int) s) & 0x800) == 0) {
			continue;
		}
		if (s->owner == 0) {
			continue;
		}
		u.offs[0][0] = 0;
		u.offs[0][1] = 0;
		u.offs[1][0] = -1;
		u.offs[1][1] = 0;
		u.offs[2][0] = -1;
		u.offs[2][1] = -1;
		u.offs[3][0] = 0;
		u.offs[3][1] = -1;
		u.offs[4][0] = 1;
		u.offs[4][1] = -1;
		u.offs[5][0] = 1;
		u.offs[5][1] = 0;
		u.offs[6][0] = 1;
		u.offs[6][1] = 1;
		u.offs[7][0] = 0;
		u.offs[7][1] = 1;
		u.offs[8][0] = -1;
		u.offs[8][1] = 1;
		if (d3sm_RaycastScreenPoint((int) map, io_ActiveCursorX, io_ActiveCursorY, &b, &a) == 0) {
			continue;
		}
		cell = 0;
		dimension = map->n;
		for (;;) {
			ix = (int) (u.offs[k][0] * (50.0 / map->sx) + b);
			iy = (int) (u.offs[k][1] * (50.0 / map->sz) + a);
			if (ix < dimension && iy < dimension) {
				cell = ((SELECTION_MAP_CELL*) map->cells)[dimension * iy + ix].id;
			}
			k++;
			if (k >= 8) {
				ix = b;
				iy = a;
				break;
			}
			if (ix < 0 || ix >= dimension || iy < 0 || iy >= dimension
			    || cell == 0 || cell == 0xd) {
				continue;
			}
			break;
		}
		if (s->f16c != 0) {
			he_AssignActionSlot(s->f16c, 0, s->id, 0);
		}
		f = s->owner;
		w = *(int*) (f + 0x28);
		if (w != -1) {
			f = (char*) evt_FindScriptById(w);
			if (f != 0) {
				evt_RequestScriptExit(f);
			}
		}
		cm_RequestWalkOnPath(s->handle, ix, iy, d3_CurrentContextIndex);
	}
	if (g_7746b8 == 0) {
		goto La50;
	}

L192f:
	if (map == 0 || g_14ce8cc == 0 || d2_HoveredWindow != -1) {
		goto La50;
	}
	fcn_0064d41a(u.buf, (char*) 0x68143c, (char*) sv_ClickedObjekt + 8);
	if (d3_FindSceneObject((char*) sv_ClickedObjekt, 0x100, 0, u.buf) == 0) {
		strcpy(u.buf, (char*) sv_ClickedObjekt);
	}
	ei = -1;
	for (idx = 0; idx < 32; idx++) {
		e = ch_ContextCharacters[idx]; p = 0;
		if (e == 0) {
			continue;
		}
		if (e[0x188] == 0) {
			continue;
		}
		cm_SendCancelCharacterActions(*(int*) (e + 4));
		if (*(int*) (e + 0x16c) != 0) {
			he_AssignActionSlot(*(int*) (e + 0x16c), 0, *(unsigned short*) e, 0);
		}
		if (*(unsigned short*) g_7746b8 == 0xfd) {
			if (d2_InteriorBuilding != 0) {
				ei = init_AllocateGebaeudeSceneSlot(d2_InteriorBuilding);
			} else if (d2_VisitedBuilding != 0) {
				ei = 0;
				p = d2_VisitedBuilding;
				goto L1a0d;
			} else {
				goto L1a0d;
			}
		} else {
			ei = init_EnsureObjektSceneContext((char*) g_7746b8);
		}
		if (d2_InteriorBuilding != 0) {
			p = (char*) d2_InteriorBuilding;
		} else if (d2_VisitedBuilding != 0) {
			p = d2_VisitedBuilding;
		}
L1a0d:
		if (ei >= 0) {
			cm_RequestUseGate(*(int*) (e + 4), *(int*) (p + 1), *(int*) ((char*) g_7746b8 + 2));
		}
	}
	sv_ClearObjectSelection();
	g_7746b8 = 0;

La50:
	if (g_7e4318 != 0) {
		he_RedirectStreifeSelection();
	}

La5d:
	g_7746f0 = 0;
	ResetDisplayCounters();
	c = 0;
	for (idx = 0; idx < 0x300; idx++) {
		s = &((SELECTION_ENTITY_SLOT*) gm_EntitySlotTable)[idx];
		e = s->owner;
		if (e != 0) {
			c = s->flag;
			if (c != sv_EntityGreyTintFlags[idx] && (*(unsigned char*) (e + 0x8c) & 0x40) == 0) {
				if (c != 0) {
					d3_SetObjectGreyTint(*(int*) (e + 0x34), 1);
				} else {
					d3_SetObjectGreyTint(*(int*) (e + 0x34), 0);
				}
			}
			c = s->flag;
			if (c != 0) {
				if (g_7746f0 == 0) {
					d2_SelectedPerson = (int) s;
				}
				g_7746f0 = g_7746f0 + 1;
				f = (char*) s->f16c;
				if (f != 0 && *(int*) (f + 1) == *(int*) (s->owner + 0x2c)
				    && !(d2_InteriorBuilding == 0
				         && (sv_SelectedBuilding == 0 || *(unsigned short*) sv_SelectedBuilding == 0x120))) {
					d2_AddDisplayCounter(s->f18c, 1);
				}
			}
		}
		sv_EntityGreyTintFlags[idx] = s->flag;
	}
	if (io_RightButtonReleased != 0 && g_7746f0 != 0) {
		sv_ClearObjectSelection();
	}
}
