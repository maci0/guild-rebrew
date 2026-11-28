#include <string.h>

extern char* d2_HoveredSceneObject;
extern unsigned short d2_CursorStateId;
extern int g_6a2bf0;
extern int g_6a2bf4;
#include "Develop/Units/d2.v1/d2_gui.h"
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
extern int g_14a79c0[];
extern char g_14a6558[];
extern char d2_HoverTextBuffer[];
extern int g_67d8cc;
extern char* g_773dfc;
extern char* sv_HoveredObjekt;
extern char* sv_HoveredBuilding;
extern char* sv_HoveredCharacter;
extern char* d2_InteriorBuilding;
extern char* d2_VisitedBuilding;
extern char* sv_SelectedBuilding;
extern unsigned short* sv_HoveredInteriorItem;
extern char* d2_SelectedBuilding;
extern int main_LoopFlags;
extern int g_7725bc;
extern int g_7746dc;
extern int g_7746e4;
extern int g_7746e0;
extern int g_7746e8;
extern int g_774798;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "game_player.h"
extern char s_6a2308[];
extern char s_6a2ff8[];
extern char s_6a3004[];
extern char s_6a300c[];
extern char s_68b3f8[];

char* __cdecl d3_FindSceneObjectAtScreenPoint(float a, float b, int flags, int mask);
void __cdecl d2_ClearAnimationSlot(int handle);
int __cdecl gm_GetEntityUiFlags(int a0, char* a1, unsigned short* a2, int a3);
char* __cdecl gm_QueryEntities(int a0, int a1, int a2, int a3);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0065f220(char* a, char* b);
int __cdecl gm_FormatEntityTitleAndName(int a1, int a2, int a3, char* a4);
int __cdecl io_FormatTextBuffer(char* buf, int a, int b);
int __cdecl fcn_0064f170(char* a, char* b, unsigned int n);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

/* ADDRESS: GOLDTL 0x0052fde0 */
void __cdecl sv_UpdateSceneHover(void)
{
	char key[0x60];
	char* cur;
	char* target;
	char* name;
	char* field;
	char* text;
	unsigned short* rec;
	unsigned int v;
	int n;
	char c;
	int limit;

	d2_HoveredSceneObject = 0;
	if (d2_CursorStateId >= 1 && d2_CursorStateId <= 8) {
		d2_HoveredSceneObject = 0;
		return;
	}
	g_6a2bf0 = io_ActiveCursorX;
	g_6a2bf4 = io_ActiveCursorY;
	if (g_6a2bf0 <= g_6a3764 || g_6a376c <= g_6a2bf0 || g_6a2bf4 <= g_6a3768 || (g_6a3770 <= g_6a2bf4 || d2_HoveredWindow != -1) || g_67d8d4 != -1
	    || ((d2_HoveredSceneObject = d3_FindSceneObjectAtScreenPoint((float) g_6a2bf0,
	    (float) g_6a2bf4, 0x20, 1)) == 0 && (d2_HoveredSceneObject = d3_FindSceneObjectAtScreenPoint((float) io_ActiveCursorX, (float) io_ActiveCursorY, 0x40, 1)) == 0)) {
		if (d2_CurrentElementId == -1 || !(*(unsigned char*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId].flags_1d0)) & 0x40)) {
			d2_HoverTextBuffer[0] = 0;
		}
		if (g_67d8cc != -1) {
			d2_ClearAnimationSlot(g_67d8cc);
			g_67d8cc = -1;
			g_774798 = -1;
		}
		g_773dfc = 0;
		sv_HoveredObjekt = 0;
		sv_HoveredBuilding = 0;
		sv_HoveredCharacter = 0;
		d2_CursorStateId = 0;
		return;
	}
	if (!(main_LoopFlags & 0x10)) {
		return;
	}
	if (g_7725bc) {
		return;
	}
	if (!d2_HoveredSceneObject) {
		return;
	}
	if (d2_HoveredWindow != -1) {
		return;
	}
	if (g_67d8d4 != -1) {
		return;
	}
	target = 0;
	g_7746dc = 0;
	g_7746e4 = 0;
	g_7746e0 = 0;
	g_7746e8 = 0;
	d2_CursorStateId = 0;
	sv_HoveredObjekt = 0;
	sv_HoveredBuilding = 0;
	sv_HoveredCharacter = 0;
	sv_HoveredInteriorItem = 0;
	cur = d2_HoveredSceneObject;
	c = cur[0x4b];
	if (c == 1) {
		sv_HoveredObjekt = *(char**) (cur + 0x204);
		if (d2_InteriorBuilding) {
			target = d2_InteriorBuilding;
		} else {
			target = 0;
		}
		g_7746dc = gm_GetEntityUiFlags((int) gm_LocalPlayerSlot, target, (unsigned short*) sv_HoveredObjekt, 0);
		if (sv_HoveredObjekt) {
			v = (unsigned int) *(unsigned short*) sv_HoveredObjekt;
			c = g_item_def_table[v * 0x41];
			if (!((c != 6 && c != 2) || !(g_7746dc & 0x4000))) {
				fcn_0064d41a(d2_HoverTextBuffer, s_68b3f8, g_14a79c0[v * 2], *(char**) 0x14a552c);
				d2_CursorStateId = 0xb;
			} else {
				fcn_0064d41a(d2_HoverTextBuffer, (char*) 0x679060, g_14a79c0[v * 2]);
				d2_CursorStateId = 0x16;
			}
		}
		g_7746e4 = g_7746dc;
		target = sv_HoveredBuilding;
	} else if (c == 2) {
		sv_HoveredBuilding = *(char**) (cur + 0x204);
		g_7746dc = gm_GetEntityUiFlags((int) gm_LocalPlayerSlot, sv_HoveredBuilding, 0, 0);
		if (sv_HoveredBuilding && !(sv_HoveredBuilding[0x5a] & 1)) {
			if (sv_HoveredBuilding[5]) {
				fcn_0064d41a(d2_HoverTextBuffer, s_6a2308, *(unsigned int*) ((unsigned int) *(unsigned char*) sv_HoveredBuilding * 0x38 + (int) g_14a6558), sv_HoveredBuilding + 5);
				g_7746e0 = g_7746dc;
				target = sv_HoveredBuilding;
			} else {
				field = *(char**) ((unsigned int) *(unsigned char*) sv_HoveredBuilding * 0x38 + (int) g_14a6558);
				strcpy(d2_HoverTextBuffer, field);
				target = sv_HoveredBuilding;
				g_7746e0 = g_7746dc;
			}
		} else {
			target = sv_HoveredBuilding;
			g_7746e0 = g_7746dc;
		}
	} else if (c == 3) {
		sv_HoveredCharacter = *(char**) (cur + 0x204);
		g_7746dc = gm_GetEntityUiFlags((int) gm_LocalPlayerSlot, 0, 0, (int) sv_HoveredCharacter);
		if (sv_HoveredCharacter && (gm_FormatEntityTitleAndName(*(unsigned short*) sv_HoveredCharacter, 1, 4, d2_HoverTextBuffer),
		    *(char*) ((int) sv_HoveredCharacter + 0x165) == 0x1c) && ((*(unsigned char*) (sv_HoveredCharacter + 0x1b4) & 1) && ((g_7746dc & 0x800) &&
		    d3_CurrentContextIndex))) {
			io_FormatTextBuffer(d2_HoverTextBuffer, 0x414c, *(unsigned short*) sv_HoveredCharacter);
			d2_CursorStateId = 0x2e;
		}
		g_7746e8 = g_7746dc;
		target = sv_HoveredBuilding;
	} else {
		d2_HoverTextBuffer[0] = 0;
		target = sv_HoveredBuilding;
	}
	if (d2_SelectedBuilding && target == d2_SelectedBuilding && (g_7746e0 & 1) && !(target[0x5a] & 1)) {
		d2_CursorStateId = 0xb;
	}
	target = d2_InteriorBuilding;
	if ((d2_InteriorBuilding || (target = d2_VisitedBuilding, d2_VisitedBuilding)) && cur) {
		if (!fcn_0064f170(cur, s_6a300c, 0xd)) {
			field = d2_HoveredSceneObject + 0x10;
			strcpy(key, field);
			if (d2_InteriorBuilding) {
				v = *(unsigned int*) (target + 0x5d);
				n = 6;
			} else {
				v = *(unsigned int*) (target + 0x5d);
				n = 2;
			}
			rec = (unsigned short*) gm_QueryEntities(v, 1, 4, n);
			while (rec) {
				name = g_item_def_table + *(unsigned short*) rec * 0x41;
				if (!fcn_0065f220(key, name + 1)) {
					sv_HoveredInteriorItem = rec;
					break;
				}
				rec = gm_NextEntityQueryMatch();
			}
			if (rec == 0) {
				if (d2_InteriorBuilding) {
					rec = (unsigned short*) gm_QueryEntities(*(unsigned int*) (target + 0x5d), 1, 0, 0xfd);
					sv_HoveredInteriorItem = rec;
				} else {
					rec = sv_HoveredInteriorItem;
				}
			}
			if (rec) {
				g_7746dc = gm_GetEntityUiFlags((int) gm_LocalPlayerSlot, target, rec, 0);
				if (g_7746dc & 1) {
					d2_CursorStateId = 0xb;
					if (*sv_HoveredInteriorItem == 0xfd) {
						text = *(char**) 0x14a5530;
						if (sv_SelectedBuilding) {
							v = g_14a79c0[*(unsigned short*) sv_SelectedBuilding * 2];
						} else {
							v = *(unsigned int*) ((unsigned int) *(unsigned char*) target * 0x38 + (int) g_14a6558);
						}
					} else {
						v = g_14a79c0[*sv_HoveredInteriorItem * 2];
						text = *(char**) 0x14a552c;
					}
					fcn_0064d41a(d2_HoverTextBuffer, s_68b3f8, v, text);
				} else {
					sv_HoveredInteriorItem = 0;
				}
			}
		}
		cur = d2_HoveredSceneObject;
	}
	if (memcmp(cur, s_6a3004, 8) == 0 && (target = *(char**) (cur + 0x204)) != 0) {
		if (g_7746dc & 1) {
			d2_CursorStateId = 0xb;
			if (target[5]) {
				fcn_0064d41a(d2_HoverTextBuffer, s_6a2ff8, *(unsigned int*) ((unsigned int) *(unsigned char*) target * 0x38 + (int) g_14a6558), target + 5, *(char**) 0x14a552c);
				cur = d2_HoveredSceneObject;
				goto done;
			}
			v = *(unsigned int*) ((unsigned int) *(unsigned char*) target * 0x38 + (int) g_14a6558);
			name = s_68b3f8;
			text = *(char**) 0x14a552c;
		} else {
			text = target + 5;
			if (!target[5]) {
				field = *(char**) ((unsigned int) *(unsigned char*) target * 0x38 + (int) g_14a6558);
				name = d2_HoverTextBuffer;
				do {
					c = *field;
					field++;
					*name = c;
					name++;
				} while (c);
				cur = d2_HoveredSceneObject;
				goto done;
			}
			v = *(unsigned int*) ((unsigned int) *(unsigned char*) target * 0x38 + (int) g_14a6558);
			name = s_6a2308;
		}
		fcn_0064d41a(d2_HoverTextBuffer, name, v, text);
		cur = d2_HoveredSceneObject;
	} else {
		field = (char*) 0x7e46c0;
		limit = 0x20;
		do {
			if (*(char**) field == cur) {
				name = field + 0x48;
				text = d2_HoverTextBuffer;
				do {
					c = *name;
					name++;
					*text = c;
					text++;
				} while (c);
				d2_CursorStateId = *(unsigned short*) (field + 0x44);
			}
			field += 0xc8;
			limit--;
		} while (limit);
	}
done:
	if (g_67d8cc == -1) {
		g_773dfc = cur;
		return;
	}
	d2_ClearAnimationSlot(g_67d8cc);
	g_67d8cc = -1;
	g_773dfc = d2_HoveredSceneObject;
	g_774798 = 0;
	return;
}
unsigned char _dpad_100f1e4[1756];
