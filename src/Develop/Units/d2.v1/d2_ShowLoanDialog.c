extern char* d2_FileObjTable;
extern char* d2_CurrentWindow;
extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction;
extern int g_14ab658;
extern int g_14ab65c;

struct loan_offer {
	int image;
	int text;
	char* line;
};

int __cdecl he_GetActiveKrediteByBorrower(int, char*, char**);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyElement(int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
void __cdecl d2_CloseWindow(int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText();
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ChooseNewLoan(char*);
void __cdecl d2_AcceptLoanOffer(char*, char*);

/* Inferred name and source home; the native registry selects this callback. */
/* ADDRESS: GOLDTL 0x005a4490 */
/* ADDRESS: GOLDDE 0x005891a0 */
void __cdecl d2_ShowLoanDialog(char* p)
{
	struct loan_offer rows[9];
	char* lines[9];
	int sel[4];
	int w;
	int h;
	int i;
	int n;
	int count;
	int prev;
	int first;
	int second;
	int refresh;
	int dialog;
	int index;
	int y;
	int slot;
	int arg;
	char* line;

	slot = -1;
	second = -1;
	count = 0;
	refresh = 1;
	prev = -1;
	for (i = 0; i < 9; i++) {
		rows[i].image = -1;
		rows[i].text = -1;
		rows[i].line = 0;
	}
	dialog = d2_LoadForm(0, 0, "locations\\geldleihe\\geldleihe_kreditaufnehmen");
	d2_CenterDialogWindows(dialog);
	d2_SetForm(dialog, 0);
	arg = d2_CurrentWindowId * 0x3cc;
	*(int*) (arg + 0x10162e8) = 0x18;
	*(int*) (arg + 0x10162ec) = 0x18;
	*(int*) (arg + 0x10162f0) = 0x18;
	*(int*) (arg + 0x10162f4) = 0x18;
	d2_SetForm(dialog, 1);
	io_AppendText(0x18c9, *(unsigned short*) (g_8680b4 + gm_ActiveTownIndex * 0x2f4) * 2 + 0x9a8);
	d2_SetOverlayAnimation(0, 0);
	while (main_RunFrameLoop(d2_ShowLoanDialog, 0x677c7) != 0) {
		if (refresh) {
			for (i = 0; i < 9; i++) {
				if (rows[i].image != -1) {
					d2_CloseWindow(rows[i].image);
					d2_DestroyElement(rows[i].text);
					rows[i].image = -1;
					rows[i].text = -1;
					rows[i].line = 0;
				}
			}
			n = he_GetActiveKrediteByBorrower(gm_LocalPlayerSlot, 0, lines);
			count = he_GetActiveKrediteByBorrower(gm_LocalPlayerSlot, p, lines);
			d2_SetForm(dialog, 4);
			io_AppendText(str_dollar_C);
			if (count >= 9) {
				io_AppendText(0x18cb);
				refresh = 1;
			} else if (count >= 3) {
				io_AppendText(0x18cc);
				refresh = 1;
			} else {
				if (count == 0) {
					io_AppendText(0x18cd, *(unsigned short*) (p + 0x27), p);
				} else {
					io_AppendText(0x18ca, *(unsigned short*) (p + 0x27), p, count, n);
				}
				refresh = 0;
			}
			d2_SetForm(dialog, 3);
			io_AppendText(str_dollar_C);
			if (refresh == 0) {
				d2_CreateButtonRow(d2_CurrentWindowId, 0, sel, 2, g_14ab658, g_14ab65c);
				first = sel[0];
				second = sel[1];
			} else {
				d2_CreateButtonRow(d2_CurrentWindowId, 0, sel, 1, g_14ab65c);
				first = -1;
				second = sel[0];
			}
			index = 0;
			h = *(short*) (d2_FileObjTable + 0x269da);
			w = *(short*) (d2_FileObjTable + 0x269d8);
			if (count > 0) {
				y = 0;
				for (i = 0; i < count; i++) {
					d2_SetForm(dialog, 2);
					rows[i].text = d2_AddElementToWindow((*(int*) (d2_CurrentWindow + 0xc) - w) >> 1, y, 0x75a, d2_CurrentWindowId);
					rows[i].image = d2_CreateChildWindow((*(int*) (d2_CurrentWindow + 0xc) - w) >> 1, y, w, h, 0x10, d2_CurrentWindowId);
					line = lines[index];
					rows[i].line = line;
					*(int*) (rows[i].image * 0x3cc + 0x10161cc) = 0x56;
					*(int*) (rows[i].image * 0x3cc + 0x1015f58) = 0x10;
					io_AppendText(0x18d6, *(unsigned int*) (line + 0xb4), *(unsigned int*) (line + 0xc0), line + 0xc4);
					index++;
					y += h + 8;
				}
			}
			if (prev != -1) {
				d2_ClearRadioGroup(prev);
				prev = -1;
			}
			if (count == 1) {
				prev = d2_CreateRadioGroup(1, rows[0].text);
			} else if (count == 2) {
				prev = d2_CreateRadioGroup(2, rows[0].text, rows[1].text);
			} else if (count == 3) {
				prev = d2_CreateRadioGroup(3, rows[0].text, rows[1].text, rows[2].text);
			}
			slot = prev;
		}
		refresh = 0;
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (second != -1) {
			arg = count > 0 && *(int*) (slot * 0x8c + 0x102cbc8) != -1;
			d2_SetElementEnabled(second, arg);
		}
		if (d2_DialogButtonAction != -1 && d2_DialogButtonAction == 2) {
			if (d2_CurrentElementId != first || first == -1) {
				if (d2_CurrentElementId == second && second != -1) {
					d2_SetFormVisibility(dialog, 0);
					d2_AcceptLoanOffer(p, rows[*(int*) (slot * 0x8c + 0x102cbc8)].line);
					refresh = 1;
					d2_SetFormVisibility(dialog, 1);
				}
			} else {
				d2_SetFormVisibility(dialog, 0);
				d2_ChooseNewLoan(p);
				d2_SetFormVisibility(dialog, 1);
				refresh = 1;
			}
		}
	}
	d2_DestroyForm(dialog);
	if (slot != -1) {
		d2_ClearRadioGroup(slot);
	}
	return d3_EndCameraAndUiMode();
}
