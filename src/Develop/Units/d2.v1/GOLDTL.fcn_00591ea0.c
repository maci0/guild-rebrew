typedef struct DialogItem {
	char pad0[0x18];
	int f18;
	char pad1c[0x58];
	int f5c;
	char pad60[0x84 - 0x60];
	int f84;
	char pad88[0x1a4 - 0x88];
	int f1a4;
} DialogItem;
#include "client_data.h"
#include "client_dialog_state.h"
void __cdecl d2_PruneBookmarkSlots(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int);
int __cdecl d2_GetFormWindow(int, int);
int __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl d2_CreateButtonRow(int, int, int*, int, int, int);
void __cdecl fcn_00476b60(void);
void __cdecl d2_ClearRadioGroup(int);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_AddToRadioGroup(int, int);
void* __cdecl gm_SearchTable67(int);
void* __cdecl gm_FindRecordById(int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowTxt(int, int, char*, int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_ClearBookmarkSlot(char*);
void __cdecl d2_SaveBookmarkSlot(int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_FocusBookmarkSlot(void);
int __cdecl main_RunFrameLoop(int, int); void __cdecl d2_DestroyForm(int);
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00591ea0 */
void __cdecl d2_RunGebHotkeysDialog(void)
{
	int clicks[2];
	int v3;
	int win;
	int old_sel;
	int last_win;
	int redraw;
	int sel;
	int item;
	int y;
	int i;
	int slot;
	unsigned char* ent;
	unsigned short* res;
	int* row;
	int b1;
	int b2;
	int b3;
	char buf[0x100];

	sel = -1;
	old_sel = -1;
	last_win = -1;
	d2_PruneBookmarkSlots();
	win = d2_LoadForm(0, 0, (char*) 0x6a9b54);
	item = win;
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 0);
	d2_InitWindowBounds(*(int*) &d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(win, 2);
	io_AppendText(0x205b);
	d2_SetForm(win, 0);
	fcn_00533f40(0x214, 0x168, *(int*) &d2_CurrentWindowId,
		d2_GetFormWindow(win, 1),
		0x38, &b1, &b2, &b3);
	d2_SetForm(win, 3);
	d2_CreateButtonRow(*(int*) &d2_CurrentWindowId, 0, clicks, 2,
		*(int*) 0x14ad4cc, *(int*) 0x14ad4c8);
	fcn_00476b60();
	redraw = 1;
	y = -0x8c;
	do {
		if (redraw) {
			d2_SetForm(win, 1);
			if (last_win != -1) {
				old_sel = *(int*) (y + (unsigned long)&g_102cbc8);
				d2_ClearRadioGroup(last_win);
			}
			d2_ClearWindowChildren(*(int*) &d2_CurrentWindowId, 1);
			last_win = d2_CreateRadioGroup(0);
			i = 0;
			y = 9;
			row = (int*) 0x779d08;
			slot = last_win * 0x8c;
			*(int*) (slot + (unsigned long)&g_102cbc0) = 1;
			do {
				ent = 0;
				res = 0;
				item = d2_AddElementToWindow(0x10, y - 5, i + 0x769, *(int*) &d2_CurrentWindowId);
				d2_AddToRadioGroup(last_win, item);
				if (row[-1] != -1)
					ent = (unsigned char*) gm_SearchTable67(row[-1]);
				if (row[0] != -1)
					res = (unsigned short*) gm_FindRecordById(row[0]);
				if (ent != 0) {
					d2_AddElementToWindow(0x60, y - 9, *ent + 0x427, *(int*) &d2_CurrentWindowId);
					io_FormatTextBuffer(buf, 0x6a9b48, *(unsigned short*) &ent[0x27], ent);
					v3 = d2_ShowTxt(0x9c, y, buf, *(int*) &d2_CurrentWindowId);
					((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[v3].width = 0x80;
					((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[v3].font = 0x54;
				} else {
					v3 = d2_ShowTxt(0x60, y, *(char**) 0x14ad494, *(int*) &d2_CurrentWindowId);
					((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[v3].font = 0x53;
				}
				if (res != 0 && *res != 0xfd) {
					d2_AddElementToWindow(0x128, y - 9, *res + 0xdf, *(int*) &d2_CurrentWindowId);
					io_FormatTextBuffer(buf, 0x6a9b44, (int) *res * 2 + 0x9a8);
					v3 = d2_ShowTxt(0x164, y + 9, buf, *(int*) &d2_CurrentWindowId);
					((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[v3].width = 0x80;
					((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[v3].font = 0x54;
				}
				row += 3;
				i++;
				y += 0x38;
			} while ((int) row < 0x779d8c);
			d2_SelectRadioGroup(last_win, old_sel);
			redraw = 0;
			item = old_sel;
			y = slot;
		}
		if (g_14ce8e0 != 0 || *(char*) &g_14cf950 == 'X' || *(char*) &g_14cf950 == 1)
			g_774654 = 1;
		if (*(int*) &g_100f1dc != -1) {
			sel = *(int*) 0x67d370;
			if (*(int*) 0x67d370 == clicks[1] && *(int*) (y + (unsigned long)&g_102cbc8) != -1) {
				d2_ClearBookmarkSlot((char*) (*(int*) (y + (unsigned long)&g_102cbc8) * 0xc + (unsigned long)&g_779d00));
				redraw = 1;
			}
			if (sel == clicks[0] && *(int*) (y + (unsigned long)&g_102cbc8) != -1) {
				d2_SaveBookmarkSlot(*(int*) (y + (unsigned long)&g_102cbc8));
				redraw = 1;
			}
		}
		d2_UpdateRadioGroup(last_win);
		i = *(int*) (y + (unsigned long)&g_102cbc8) != -1 &&
			*(int*) (*(int*) (y + (unsigned long)&g_102cbc8) * 0xc + 0x779d04) != -1;
		d2_SetElementEnabled(clicks[1], i);
		d2_SetElementEnabled(clicks[0], *(int*) (y + (unsigned long)&g_102cbc8) != -1);
		d2_FocusBookmarkSlot();
	} while (main_RunFrameLoop((int) d2_RunGebHotkeysDialog, 0x657c7));
	d2_ClearRadioGroup(last_win);
	d2_DestroyForm(win);
}
