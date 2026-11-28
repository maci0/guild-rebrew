extern int d2_CurrentWindowId;
extern char* d2_Controls;
extern unsigned char* lpGebaeudePROT;
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
extern unsigned short g_7f3ee4;
extern int g_90d520[];
extern int g_14a79c0[];
extern char str_fmt_s[];
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl gm_CollectTradeItemsByKind(int);
int __cdecl fcn_00502cd0(int, int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl fcn_0064d41a(char*, const char*, ...);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_ClearInputState(void);
#include "Develop/Units/d2.v1/d2_gui.h"
/* Route one enhanced-building selection through the query engine: build the
 * window, walk the candidate query, spawn one icon record per hit, then keep
 * dispatching until the master loop closes the dialog. */
/* ADDRESS: GOLDTL 0x004be560 */
unsigned int __cdecl d2_ShowRoutingChooseGoodDialog(char* building, int a1, unsigned int a2)
{
	int items[10];
	unsigned char* src;
	char* q;
	char* e;
	int win;
	int t;
	int n;
	int i;
	unsigned int ret;

	ret = a2;
	src = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char) *building];
	a2 = d2_LoadForm(0, 0, (char*) 0x6816e8);
	d2_CenterDialogWindows(a2);
	d2_SetForm(a2, 4);
	d2_GetWindowListItem(a2, 4, io_AppendText(0x7d));
	d2_SetForm(a2, 2);
	win = a2;
	if ((((BUILDING_PROTOTYPE*)src)->category) == 0x1c) {
		q = (char*) fcn_00502cd0(*(int*) (building + 0x5d), 2, 0, 0x1dc, 6);
		n = 0;
		if (!q) {
			goto tail;
		}
		e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
		if (!e) {
			goto tail;
		}
		do {
			if (*(int*) (e + 0xe) > 1) {
				t = d2_AddElementToWindow((n % 4) * 0x40, (n / 4) * 0x40,
					*(unsigned short*) e + 0xdf, d2_CurrentWindowId);
				items[n] = t;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_05c) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].flags_1d0) = 3;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_1e4) = 0x525;
				g_90d520[n] = *(unsigned short*) e;
				n++;
			}
			e = (char*) gm_NextEntityQueryMatch();
		} while (e);
	} else if ((((BUILDING_PROTOTYPE*)src)->category) == 9) {
		q = (char*) fcn_00502cd0(*(int*) (building + 0x5d), 2, 0, 0x116, 6);
		n = 0;
		if (!q) {
			goto tail;
		}
		e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
		if (!e) {
			goto tail;
		}
		do {
			if (*(int*) (e + 0xe) >= 1) {
				t = d2_AddElementToWindow((n % 4) * 0x40, (n / 4) * 0x40,
					*(unsigned short*) e + 0xdf, d2_CurrentWindowId);
				items[n] = t;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_05c) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].flags_1d0) = 3;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_1e4) = 0x525;
				g_90d520[n] = *(unsigned short*) e;
				n++;
			}
			e = (char*) gm_NextEntityQueryMatch();
		} while (e);
	} else {
		gm_CollectTradeItemsByKind((int) building);
		q = (char*) fcn_00502cd0(*(int*) (building + 0x5d), 2, 0, 0xff, 6);
		n = 0;
		for (i = 0; i < g_7f3ee4; i++) {
			e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, g_90d520[n]);
			if (e && *(int*) (e + 0xe) > 1) {
				t = d2_AddElementToWindow((n % 4) * 0x40, (n / 4) * 0x40,
					g_90d520[n] + 0xdf, d2_CurrentWindowId);
				items[n] = t;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_05c) = 1;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].flags_1d0) = 0x23;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_1e4) = 0x525;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_1dc) = 4;
				*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_1e0) = 0xf;
				fcn_0064d41a((char*) ((char*) &((D2_CONTROL_TL*) (d2_Controls))[t] + 0xcc),
					"%s", g_14a79c0[g_90d520[n] * 2]);
				n++;
			}
		}
	}
tail:
	g_7f3ee4 = (unsigned short) n;
	g_90d520[n] = 0;
	t = d2_AddElementToWindow((n % 4) * 0x40 + 7, (n / 4) * 0x40 + 7, 0x527, d2_CurrentWindowId);
	items[n] = t;
	*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].value_05c) = 1;
	*(unsigned int*) (&((D2_CONTROL_TL*) (d2_Controls))[t].flags_1d0) = 3;
	while (main_RunFrameLoop(0x4be560, 0x657c7)) {
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			for (t = 0; t < g_7f3ee4 + 1; t++) {
				if (d2_CurrentElementId == items[t]) {
					ret = g_90d520[t];
					d2_DialogCloseRequested = 1;
					break;
				}
			}
		}
	}
	d2_DestroyForm(win);
	io_ClearInputState();
	return ret;
}
