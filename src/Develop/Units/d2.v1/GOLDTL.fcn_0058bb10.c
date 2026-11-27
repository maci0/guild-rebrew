/* Picker screen arm for the supplier/slot dialog.
 *
 * Body shape: creates the dialog context with fcn_00470820(0, 0, 0x6a969c),
 * registers the eight widget rows (fcn_004727a0 0,1,2,3,6,4,5,7), feeds the
 * title through the fcn_00519190 markup expander, fills the local dialog block
 * through the three widget ctors (fcn_0058b030 selection list, fcn_0058b1f0
 * slot rows, fcn_0058b440 trade rows), then loops while
 * fcn_005373e0(0x58bb10, 0x677c7) asks for another pass. Each pass rescans the
 * focus handle at 0x67d370 against the three candidate tables, rebuilds only
 * the groups whose dirty bits are set, and hands the focus change to the
 * per-case callback while gating with fcn_00471af0. The selection result goes
 * to arg1.
 *
 * Native extent 0x58bb10-0x58bfc4 (0x4b4 bytes): frame 0x1dc, one ret, 334
 * instructions, 31 calls, 70 pushes, one indirect call through the callback
 * argument. The three caller arms (0x58fa20, 0x58fb60, 0x58fba0) forward
 * (0, entity, table pointer, selector, callback) and each ends with a jump to
 * 0x532ef0. */

typedef struct {
	int btn;                        /* 0x00 focus widget handle */
	char* item;                     /* 0x04 */
	int id;                         /* 0x08 */
	char kind;                      /* 0x0c */
	char pad0d[3];
} DialogEntry;                          /* SIZE 0x10 */

typedef struct {
	int handle;                     /* 0x000 */
	int filter;                     /* 0x004 */
	int slot;                       /* 0x008 */
	int trade_form; int font;
	int owner;                      /* 0x014 */
	int form5; int form7; int ids[4];               /* 0x018, overlays SelDlg::ids */
	int type;                       /* 0x030 */
	DialogEntry entries[16];        /* 0x034 */
	int selected;                   /* 0x134 */
	int button; int rows[8][3];     /* 0x138, 0x13c */
	int row;                        /* 0x19c */
} DialogState;                          /* SIZE 0x1a0 */

typedef struct {
	int dlg;                        /* 0x00 */
	char pad4[0x0c];
	int font;                       /* 0x10 */
	char pad14[0x0c];
	int ids[4];                     /* 0x20 */
	int sel;                        /* 0x30 */
} SelDlg;                               /* SIZE 0x34 */

typedef struct {
	char* item;                     /* 0x00 */
	int value;                      /* 0x04 */
	unsigned char kind;             /* 0x08 */
	char pad09[3];
	char* item2;                    /* 0x0c */
	int value2;                     /* 0x10 */
} PickResult;                           /* SIZE 0x14 */

extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern volatile int g_6b7fac;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern char g_6a969c[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0058b030(char*, SelDlg*);
void __cdecl d2_PopulateBuildingSlotList(char*, DialogState*, unsigned int);
void __cdecl fcn_0058b440(unsigned int, unsigned int*, int, int);
char __cdecl gm_GetEntitySlotIndex(int, void*);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x0058bb10 */
void __cdecl d2_RunGraveyardPickerDialog(PickResult* result, char* graveyard, int titleId, int mode,
			  void (__cdecl* callback)(char*, PickResult*))
{

	DialogState st;

	PickResult rec; PickResult rec1;

	int saved;
	unsigned int deadline;
	int cur;
	int selft;
	int i;
	int flags;
	int found;

	deadline = (unsigned int)g_6b7fac;
	if (result != 0) {
		result->item = 0;
		result->item2 = 0;
	}
	st.handle = d2_LoadForm(0, 0, g_6a969c);

	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(st.handle);
	d2_SetForm(st.handle, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(st.handle, 1);
	st.filter = d2_CurrentWindowId;

	io_AppendText((int) g_6a9694, titleId);
	d2_SetForm(st.handle, 2);
	st.slot = d2_CurrentWindowId;
	d2_SetForm(st.handle, 3);
	st.trade_form = d2_CurrentWindowId;
	d2_SetForm(st.handle, 6);
	st.font = d2_CurrentWindowId;
	d2_SetForm(st.handle, 4);
	st.owner = d2_CurrentWindowId;
	d2_SetForm(st.handle, 5);
	st.form5 = d2_CurrentWindowId;
	d2_SetForm(st.handle, 7);
	st.form7 = d2_CurrentWindowId;

	st.type = 0; st.selected = 0; st.row = 0;
	fcn_0058b030(graveyard, (SelDlg*)&st);
	d2_PopulateBuildingSlotList(graveyard, &st, 0xffffffff);
	fcn_0058b440((unsigned int) graveyard, (unsigned int*) &st, -1, mode);
	g_100f1dc = -1;
	deadline += 0x96;
	selft = st.selected;

	for (;;) {
		flags = 0;
		cur = selft;
		saved = st.type;
		found = 0;
		if ((unsigned int)g_6b7fac > deadline) {
			flags = 7;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			for (i = 0; i < 4 && !found; i++) {
				if (st.ids[i] == d2_CurrentElementId && i != st.type) {
					selft = 0;
					st.type = i; cur = -1;
					st.selected = 0;
					flags |= 7;
					found = 1;
				}
			}
			for (i = 0; !found && i < 16; i++) {
				if (st.entries[i].btn == d2_CurrentElementId && i != cur) {
					selft = i;
					st.selected = i;
					flags |= 3;
					found = 1;
				}
			}
			if (mode == 0) {
				for (i = 0; !found && i < 8; i++) {
					if (st.rows[i][0] == d2_CurrentElementId) {
						st.row = i;
						found = 1;
						if (result != 0) {
							result->item = st.entries[selft].item;
							result->value = *(int*) result->item;
							result->kind = (unsigned char) gm_GetEntitySlotIndex(*(int*) (graveyard + 0x65), result->item);
							result->item2 = (char*) st.rows[i][1];
							result->value2 = *(int*) result->item2;
						}
						if (callback != 0) {
							rec.item = st.entries[selft].item;
							rec.value = *(int*) rec.item;
							rec.kind = (unsigned char) gm_GetEntitySlotIndex(*(int*) (graveyard + 0x65), rec.item);
							rec.item2 = (char*) st.rows[i][1];
							rec.value2 = *(int*) rec.item2;
							d2_SetFormVisibility(st.handle, 0);
							callback(graveyard, &rec);
							d2_SetFormVisibility(st.handle, 1);
						} else if (result != 0) {
							g_774654 = 1;
						}
					}
				}
			} else if (mode == 1 && st.button == d2_CurrentElementId) {
				if (result != 0) {
					result->item = st.entries[selft].item;
					result->value = *(int*) result->item;
					result->kind = (unsigned char) gm_GetEntitySlotIndex(*(int*) (graveyard + 0x65), result->item);
					result->item2 = 0;
					result->value2 = -1;
				}
				if (callback != 0) {
					rec1.item = st.entries[selft].item;
					rec1.value = *(int*) rec1.item;
					rec1.kind = (unsigned char) gm_GetEntitySlotIndex(*(int*) (graveyard + 0x65), rec1.item);
					rec1.item2 = 0;
					rec1.value2 = -1;
					d2_SetFormVisibility(st.handle, 0);
					callback(graveyard, &rec1);
					d2_SetFormVisibility(st.handle, 1);
				} else if (result != 0) {
					g_774654 = 1;
				}
			}
		}
		if (flags & 4) {
			fcn_0058b030(graveyard, (SelDlg*)&st);
			selft = st.selected;
		}
		if (flags & 2) {
			d2_PopulateBuildingSlotList(graveyard, &st, saved);
			selft = st.selected;
		}
		if (flags & 1) {
			fcn_0058b440((unsigned int) graveyard, (unsigned int*) &st, cur, mode);
			selft = st.selected;
		}
		if (main_RunFrameLoop((void*) 0x58bb10, 0x677c7) == 0) {
			d2_DestroyForm(st.handle);
			return;
		}
	}
}
