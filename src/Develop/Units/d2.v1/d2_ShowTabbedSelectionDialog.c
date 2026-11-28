#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned int g_775344;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
extern int g_14ce8e8;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern volatile unsigned int gm_GameTicks;
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

/* Private layout views inferred from native accesses; they allocate no
 * storage and are visible only to this translation unit. */

// SIZE 0x38
typedef struct {
	void* ent;
	int key1;
	int key2;
	char pad0c[0x2c];
} SelRow_5ccca0;

// SIZE 0x14
typedef struct {
	int bild;
	unsigned int count;
	int element;
	int (__cdecl *create)(void*, int, void*, void*);
	void (__cdecl *present)(int, int, int, int, void*);
} TabRec_5ccca0;

extern TabRec_5ccca0 g_6ac8a8[];
#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/Units/d2.v1/d2_win.h"
int __cdecl d2_AddWindowTextButton(int, int, int, int, int);
void __cdecl d2_SetElementWidth(int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ClearAndScrollSubform(int, int, int);
void __cdecl d2_ClearTabGroups(void);
void __cdecl d2_UpdateMatchAttitudeBars(int, int, void*);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005ccca0 */
int __cdecl d2_ShowTabbedSelectionDialog(void* ent, char* name, int tab, int callback)
{
	SelRow_5ccca0 rows[16];
	void* cur;
	int h;
	int i;
	int n;
	int old;

	int y;
	int step;
	int rem;
	int state;
	int result;
	unsigned int time0;
	int sel;
	int win;

	sel = 0;
	time0 = gm_GameTicks;
	d2_ClearTabGroups();
	if (tab > -1 && tab < 8) {
		g_775344 = tab;
	}
	if (g_775344 >= 8) {
		g_775344 = 0;
	}
	for (i = 0; i < 8; i++) {
		g_6ac8a8[i].count = g_6ac8a8[i].create(
				(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0, rows, ent);
	}
	if (g_6ac8a8[g_775344].count == 0) {
		g_775344 = 8;
		for (i = 0; i < 8; i++) {
			if (g_6ac8a8[i].count != 0) {
				g_775344 = i;
				break;
			}
		}
	}
	h = d2_LoadForm(0, 0, "panel\\geb_liste");
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 2);
	win = d2_CurrentWindowId;
	d2_SetForm(h, 1);
	io_AppendText(name);
	d2_SetForm(h, 4);
	rem = ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].height - 0x107;
	step = rem / 7;
	rem = rem % 7;
	y = 0;
	for (i = 0; i < 8;) {
		g_6ac8a8[i].element = d2_AddWindowTextButton(
				(((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width - 0xb9) / 2, y, 0xbf,
				*(int*) (0x14aad40 + g_6ac8a8[i].bild * 4), d2_CurrentWindowId);
		d2_SetElementWidth(g_6ac8a8[i].element, 0xb9);
		i++;
		y += 0x21 + step + (--rem >= 0);
	}
	if (g_775344 < 8) {
		d2_SetForm(h, 2);
		g_6ac8a8[g_775344].count = g_6ac8a8[g_775344].create(
				(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0x10, rows, ent);
		g_6ac8a8[g_775344].present(h, 2, 3, g_6ac8a8[g_775344].count, rows);
	}
	d2_DialogButtonAction = -1;
	state = 3;
	cur = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
	do {
		if (state == 3) {
			old = -1;
			if (g_775344 >= 8) {
				g_775344 = 0;
			} else {
				old = g_6ac8a8[g_775344].count;
			}
			for (i = 0; i < 8; i++) {
				g_6ac8a8[i].count = g_6ac8a8[i].create(
						(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0, rows, ent);
			}
			if (g_6ac8a8[g_775344].count == 0) {
				g_775344 = 8;
				for (i = 0; i < 8; i++) {
					if (g_6ac8a8[i].count != 0) {
						g_775344 = i;
						break;
					}
				}
			}
			for (i = 0; i < 8; i++) {
				d2_SetElementEnabled(g_6ac8a8[i].element, g_6ac8a8[i].count > 0);
				*(int*) ((char*)&((D2_CONTROL_TL*)d2_Controls)[g_6ac8a8[i].element] + 0x38) =
						i == g_775344;
			}
			if (g_775344 < 8) {
				n = g_6ac8a8[g_775344].create(
						(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0x10, rows, ent);
				g_6ac8a8[g_775344].count = n;
				if (n != old) {
					g_6ac8a8[g_775344].present(h, 2, 3, n, rows);
				} else {
					g_6ac8a8[g_775344].present(h, 2, -1, n, rows);
				}
				d2_UpdateMatchAttitudeBars(cur, g_6ac8a8[g_775344].count, rows);
			} else {
				d2_ClearAndScrollSubform(h, 2, 3);
				cur = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
			}
		} else if (state == 1) {
			i = g_6ac8a8[sel].create(
					(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0, 0, ent);
			g_6ac8a8[sel].count = i;
			if (i != 0) {
				*(int*) ((char*)&((D2_CONTROL_TL*)d2_Controls)[g_6ac8a8[g_775344].element] + 0x38) = 0;
				g_775344 = sel;
				*(int*) ((char*)&((D2_CONTROL_TL*)d2_Controls)[g_6ac8a8[sel].element] + 0x38) = 1;
				n = g_6ac8a8[g_775344].create(
						(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 0x10, rows, ent);
				g_6ac8a8[g_775344].count = n;
				g_6ac8a8[g_775344].present(h, 2, 3, n, rows);
			} else {
				d2_SetElementEnabled(g_6ac8a8[sel].element, 0);
			}
		} else if (state == 4) {
			d2_UpdateMatchAttitudeBars(cur, g_6ac8a8[g_775344].count, rows);
		} else if (state == 2) {
			time0 = 0;
		}
		result = 0;
		state = 0;
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (g_14ce8e8 != 0) {
			if (cur == (void*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot])) {
				result = 0;
				cur = 0;
				for (i = 0; i < g_6ac8a8[g_775344].count; i++) {
					if (rows[i].key2 == d2_CurrentElementId) {
						if (i > -1 && i < g_6ac8a8[g_775344].count) {
							if (rows[i].ent != 0 &&
									*(unsigned short*) rows[i].ent != 0xffff) {
								state = 4;
								cur = rows[i].ent;
							}
						}
						break;
					}
				}
				goto after;
			}
			goto hit;
		} else {
			if (cur != (void*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot])) {
				state = 4;
				cur = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
			} else {
				goto hit;
			}
		}
		goto after;
	hit:
		if (d2_DialogButtonAction != -1) {
			for (i = 0; i < 8; i++) {
				if (g_6ac8a8[i].element == d2_CurrentElementId) {
					state = 1;
					sel = i;
					goto after;
				}
			}
			for (i = 0; i < g_6ac8a8[g_775344].count; i++) {
				if (rows[i].key1 == d2_CurrentElementId) {
					state = 2;
					sel = i;
					if (callback == 0) {
						result = (int) rows[i].ent;
						d2_DialogCloseRequested = 1;
					} else {
						d2_SetFormVisibility(h, 0);
						if (((int (__cdecl*) (void*, int)) callback)(
									rows[i].ent, 0) != 0) {
							result = (int) rows[i].ent;
						} else {
							result = 0;
						}
						d2_SetFormVisibility(h, 1);
					}
				}
			}
		} else if (time0 <= gm_GameTicks &&
				*(int*) &((D2_WIN*)d2_Windows)[win].pad3c[0x224] == 0) {
			state = 3;
			time0 = gm_GameTicks + 0xd8;
		}
	after:
		if (main_RunFrameLoop((void*) d2_ShowTabbedSelectionDialog, 0x657c7) == 0) {
			break;
		}
	} while (1);
	d2_DestroyForm(h);
	return result;
}
