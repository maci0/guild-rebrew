#include <string.h>
#pragma pack(push, 1)
typedef struct {
    unsigned char kind, unknown001[0x22];
    short entries[0x40]; unsigned char unknown0a3[0x1aa];
} GROUNDPLAN_BLD_PROTO;
#pragma pack(pop)
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect47bf;

typedef struct {
	char pad0[0x18];
	int* items;
} D2_SPRITE_SET;

extern int d3_CurrentContextIndex;
extern int g_6a2be4;
extern int g_1040494;
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern unsigned char gm_ActiveTownIndex;
extern char gm_TownTable[];
extern char* sv_SelectedBuilding;
extern char* d2_VisitedBuilding;
extern char* d2_InteriorBuilding;
extern char* g_774718;
extern char* g_77471c;
extern int g_774714;
extern char* tp_d2_GroundplanSurface;
extern char* d2_GroundplanMaskSurface;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_EntityBlockedField[];
extern int g_14ce8d8;
extern int d2_ScreenSurface;
extern int d2_ResourceOffset;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
extern int g_7ea380[15];
extern char str_empty[];

extern char* g_14a79c0[];

void __cdecl d2_DestroyElement(int id);
void __cdecl d2_LoadBuildingGroundplan(void);
int __cdecl d2_FindResourceByName(const char* name);
void* __cdecl d2_GetResourceData(int idx);
int __cdecl d2_DrawSpriteFromSet(int x, int y, int a3, D2_SPRITE_SET* s,
	int idx);
void* __cdecl d2_QueueTexturedQuad(int x, int y, int w, int h, int tex,
	Rect47bf* src);
int __cdecl d2_LockSurface(void* s);
void __cdecl d2_ReadSurfacePixel(int x, int y, void* s, unsigned char* dst);
int __cdecl d2_CompareRgb(char* a1, char* a2);
int __cdecl d2_UnlockSurface(void* o);
unsigned short* __cdecl gm_QueryEntities(int container_id, int arg_count, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl d2_DispatchTutorialEvent(int a, int b, int c, int d);
int __cdecl gm_GetEntityUiFlags(int a, int b, void* c, int d);
void __cdecl gm_ChangeBuildingRoom(int n, int v);
void __cdecl d2_SetMouseTooltip(char* a);
void __cdecl d2_EnterBuildingObjekt(int a, int b, int c);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strupr(char*);

/* ADDRESS: GOLDTL 0x005279f0 */
void __cdecl d2_UpdateBuildingGroundplan(unsigned int inputFlags)
{
	int v9;
	int v6;
	int v7;
	int x;
	int y;
	int id;
	char key[4];
	Rect47bf r;
	char name[128];
	char path[128];
	unsigned short* v8;
	short* e;
	char* p;
	char* q;
	char* s;
	char* d;
	char c;

	if (d3_CurrentContextIndex != g_6a2be4 || sv_SelectedBuilding != g_77471c
		|| d2_VisitedBuilding != g_774718 || g_774714 != 0) {
		g_774718 = d2_VisitedBuilding;
		g_77471c = sv_SelectedBuilding;
		p = (char*)g_7ea380;
		do {
			if (*(int*) p != -1) {
				d2_DestroyElement(*(int*) p);
				*(int*) p = -1;
			}
			p += 4;
		} while ((int) p < (int)(g_7ea380 + 15));
		if (d2_VisitedBuilding || d2_InteriorBuilding)
			d2_LoadBuildingGroundplan();
		g_6a2be4 = d3_CurrentContextIndex;
	}
	if (!d2_VisitedBuilding && !d2_InteriorBuilding) {
		s = gm_TownTable + (unsigned int) gm_ActiveTownIndex * 0x2f4;
		d = name;
		do {
			c = *s;
			*d = c;
			s++;
			d++;
		} while (c);
		strupr(name);
		sprintf(path, "_STADTWAPPEN_%s", name);
		v6 = d2_FindResourceByName(path);
		if (v6 == -1)
			v6 = d2_FindResourceByName("_STADTWAPPEN_BERLIN");
		v7 = (int) d2_GetResourceData(v6);
		d2_DrawSpriteFromSet(g_1040494 - 0x6e, 0x5b, d2_ScreenSurface,
			(D2_SPRITE_SET*) v7, d2_ResourceOffset + 1);
	} else {
		if (tp_d2_GroundplanSurface) {
			r.left = 0;
			r.top = 0;
			r.right = *(int*) (tp_d2_GroundplanSurface + 0x54);
			r.bottom = *(int*) (tp_d2_GroundplanSurface + 0x58);
			d2_QueueTexturedQuad(g_1040494 - 0x6e, 0x5b, 0x68, 0x6e,
				*(int*) (tp_d2_GroundplanSurface + 0x20), &r);
		}
		if (inputFlags & 0x2000) {
			x = (io_ActiveCursorX - g_1040494) + 0x72;
			y = io_ActiveCursorY - 0x59;
			if (d2_GroundplanMaskSurface && x >= 0 && x < *(int*) (d2_GroundplanMaskSurface + 4)
				&& y >= 0 && y < *(int*) (d2_GroundplanMaskSurface + 8)) {
				d2_LockSurface(d2_GroundplanMaskSurface);
				d2_ReadSurfacePixel(x, y, d2_GroundplanMaskSurface, (unsigned char*) key);
				v6 = 0;
				q = (char*) 0x6a24ec;
				do {
					if (!d2_CompareRgb(key, q))
						break;
					q += 3;
					v6++;
				} while ((int) q < 0x6a2519);
				d2_UnlockSurface(d2_GroundplanMaskSurface);
				if (v6 < 0xf) {
					if (d2_VisitedBuilding) {
						BUILDING_PROTOTYPE* bp = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[(unsigned char) *d2_VisitedBuilding];
						v8 = 0;
						v9 = 0;
						if (bp->category == 2) {
							v8 = gm_QueryEntities(*(int*) (d2_VisitedBuilding + 0x5d),
								1, 4, 2);
							while (v8) {
								if (*v8 != 0xfd) {
									if (v9 == v6)
										break;
									v9++;
								}
								v8 = (unsigned short*) gm_NextEntityQueryMatch();
							}
						} else {
							for (v7 = 0; v7 < 0x40; v7++) {
								if (bp->components[v7] != 0xffff) {
									id = bp->components[v7] & 0x7fff;
									if ((((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind == 2
										|| ((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind == 6)
										&& id != 0xfd) {
										if (v9 == v6) {
											v8 = gm_QueryEntities(
												*(int*) (d2_VisitedBuilding + 0x5d),
												1, 0, id);
											break;
										}
										v9++;
									}
								}
							}
						}
						if (g_14ce8d8) {
							if (!v8)
								goto label_527db2;
							if (*v8 != *(unsigned short*) sv_SelectedBuilding
								&& d2_DispatchTutorialEvent(0x19, (int) d2_VisitedBuilding, 0,
									(int) *v8) == 1
								&& gm_EntityBlockedField[gm_LocalPlayerSlot * 0x21c] <= 0) {
								if (gm_GetEntityUiFlags(gm_LocalPlayerSlot,
									(int) d2_VisitedBuilding, v8, 0) & 0x4000)
									gm_ChangeBuildingRoom(-1, (int) *v8);
								goto label_527db2;
							}
						}
						if (v8)
							d2_SetMouseTooltip(g_14a79c0[(unsigned short) *v8 * 2]);
					}
label_527db2:
					if (d2_InteriorBuilding) {
						BUILDING_PROTOTYPE* bp = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[(unsigned char) *d2_InteriorBuilding];
						v8 = 0;
						v9 = 0;
						for (v7 = 0; v7 < 0x40; v7++) {
							if (bp->components[v7] != 0xffff) {
								id = bp->components[v7] & 0x7fff;
								if ((((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind == 2
									|| ((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind == 6)
									&& id != 0xfd) {
									if (v9 == v6) {
										v8 = gm_QueryEntities(
											*(int*) (d2_InteriorBuilding + 0x5d),
											1, 0, id);
										break;
									}
									v9++;
								}
							}
						}
						if (g_14ce8d8) {
							if (!v8)
								goto done;
							if ((!sv_SelectedBuilding || (*v8 != *(unsigned short*) sv_SelectedBuilding
								&& d2_DispatchTutorialEvent(0x19, (int) d2_InteriorBuilding, 0,
									(int) *v8) == 1))
								&& gm_EntityBlockedField[gm_LocalPlayerSlot * 0x21c] <= 0) {
								if (!(gm_GetEntityUiFlags(gm_LocalPlayerSlot,
									(int) d2_InteriorBuilding, v8, 0) & 0x4000))
									goto done;
								d2_EnterBuildingObjekt((int) d2_InteriorBuilding,
									*(int*) ((char*) v8 + 2), (int) str_empty);
								goto done;
							}
						}
						if (v8)
							d2_SetMouseTooltip(g_14a79c0[(unsigned short) *v8 * 2]);
					}
				}
			}
		}
	}
done:
	g_774714 = 0;
}
unsigned char _dpad_773de8[2156];
unsigned char _dpad_7f4cc0[401] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
unsigned char _dpad_14a579c[8740];
unsigned char _dpad_14a79c0[17000];
