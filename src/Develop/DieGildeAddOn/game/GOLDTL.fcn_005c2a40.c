#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char* g_entity_type_table;
extern char* g_item_def_table;
extern char* g_1015ea0;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern int d2_CurrentWindowId;
extern int g_7747b4;
extern double g_662ad8;
extern double g_662908;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern char g_6ac628[];
extern char g_6ac618[];

int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
unsigned short* __cdecl fcn_00502cd0(int, int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
void __cdecl fcn_00533f40(int, int, int, int);
float __cdecl eval_ObjektPreis2Credits(int, int);
int __cdecl d2_AddElementToWindow(int, int, char*, int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00476b60(void);
char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00526120(int, int);
int __cdecl gm_CheckEntityStock(void*, int, unsigned char);
char* __cdecl cm_SendLogAction(char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_SendCopyEntityData(char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl gm_GetElapsedMinutes(char*, char*);
void __cdecl fcn_0046f940(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005c2a40 */
void __cdecl fcn_005c2a40(unsigned char* productionBuilding)
{
	int slots[96];
	int coord_x;
	int coord_y;
	int child;
	char msg[0x100];
	char* base;
	char* r;
	unsigned short* p;
	int* ep;
	int nslots;
	int total;
	int others;
	int removed;
	int han;
	int cnt;
	int sel;
	int i;
	int id;
	int handle;
	int val;
	int owner;
	float scale;
	float lo;
	float hi;

	nslots = 0;
	removed = 0;
	others = 0;
	total = 0;
	owner = *(int*) (productionBuilding + 1);
	ep = slots;
	for (i = 0x20; i != 0; i--) {
		ep[1] = -1;
		ep[2] = -1;
		ep[0] = 0;
		ep += 3;
	}
	if (he_StartHandlungSearch(2, 0, 0x1f, 3, owner) != 0) {
		do {
			total++;
		} while (he_fn_Handlung() != 0);
	}
	base = g_entity_type_table + (int) (*productionBuilding) * 0x24d;
	p = (unsigned short*) (base + 0x23);
	for (i = 0; i < 0x40; i++) {
		if (nslots >= 0x20) {
			break;
		}
		if (*p != 0xffff) {
			id = *p & 0x7fff;
			if ((g_item_def_table[id * 0x41] == 2 || g_item_def_table[id * 0x41] == 6)
			    && id != 0xfd) {
				slots[nslots * 3] = id;
				nslots++;
			}
		}
		p++;
	}
	p = fcn_00502cd0(*(int*) (productionBuilding + 0x5d), 1, 5, 0);
	while (p != 0) {
		if ((g_item_def_table[(int) (*p) * 0x41] == 2 || g_item_def_table[(int) (*p) * 0x41] == 6)
		    && *p != 0xfd) {
			others++;
		}
		p = gm_NextEntityQueryMatch();
	}
	han = fcn_00470820(0, 0, g_6ac628);
	d2_CenterDialogWindows(han);
	d2_SetForm(han, 1);
	io_AppendText(0x17ce);
	d2_SetForm(han, 0);
	if (nslots > 4) {
		fcn_00533f40((*(int**) 0x77255c)[4] - 0x4c, (*(int**) 0x77255c)[3] - 0x20,
		             d2_CurrentWindowId,
		             fcn_00472830(han, 2, 0x3c, &coord_y, &coord_x, &child));
		((D2_CONTROL_TL*) (g_1015ea0))[child].font = 0x56;
	}
	d2_SetForm(han, 2);
	cnt = 0;
	for (i = 0; i < nslots; i++) {
		id = slots[i * 3];
		scale = (float) ((double) g_7747b4 * 0.25 + 0.5);
		val = (int) (eval_ObjektPreis2Credits(id, 100) * scale);
		handle = d2_AddElementToWindow(0x10, cnt, (char*) (id + 0xdf), d2_CurrentWindowId);
		slots[i * 3 + 1] = handle;
		((D2_CONTROL_TL*) g_1015ea0)[handle].value_05c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[handle].flags_1d0 = 3;
		((D2_CONTROL_TL*) g_1015ea0)[handle].value_1e4 = 0x520;
		((D2_CONTROL_TL*) g_1015ea0)[handle].value_1e8 = -2;
		((D2_CONTROL_TL*) g_1015ea0)[handle].value_1ec = -2;
		io_FormatTextBuffer(msg, 0x17d3,
		             *(int*) (id * 8 + 0x14a79c0), val);
		slots[i * 3 + 2] = fcn_0046fac0(0x60, cnt + 10, msg, d2_CurrentWindowId);
		cnt += 0x3c;
	}
	d2_SetOverlayAnimation(0, 0);
	fcn_00476b60();
	do {
		r = gm_SearchTable67(owner);
		if ((productionBuilding[0x5b] & 4) != 0 || r == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0 || g_100f1dc == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && nslots > 0) {
			ep = slots + 1;
			sel = 0;
			do {
				if (d2_CurrentElementId == *ep) {
					scale = (float) ((double) g_7747b4 * 0.25 + 0.5);
					val = (int) (eval_ObjektPreis2Credits(slots[sel * 3], 100) * scale);
					if (total + others >= (int) (unsigned char) *(base + 0x21)) {
						fcn_00526120(*(int*) 0x14ab260, 0);
					} else if (gm_CheckEntityStock((void*) (g_7f4ca0 +
					                                 (int) g_774970 * 0x21c),
					                        val, g_773d75) != 0) {
						memset(msg, 0, 0xf8);
						msg[4] = 0x1f;
						*(int*) (msg + 8) =
						    *(int*) (g_7f4ca4 +
						             (int) g_774970 * 0x21c);
						*(int*) (msg + 0xc) = *(int*) (productionBuilding + 1);
						*(int*) (msg + 0x28) = *(int*) &gm_GameTime;
						*(int*) (msg + 0x2c) = g_7f4c04;
						*(int*) (msg + 0x30) = g_7f4c08;
						*(short*) (msg + 0x34) = g_7f4c0c;
						msg[0x36] = 1;
						*(short*) (msg + 0x5c) =
						    (short) slots[sel * 3];
						*(int*) (msg + 0x58) = *(int*) (productionBuilding + 1);
						cm_SendLogAction(g_6ac618);
						cm_RequestMoveCredits(-1,
						             *(int*) (g_7f4ca4 +
						                     (int) g_774970 * 0x21c),
						             (char) g_773d75, val);
						cm_SendCopyEntityData(msg);
						cm_SendTraceEnd(g_6ac618);
					}
					break;
				}
				sel++;
				ep += 3;
			} while (sel < nslots);
		}
		total = 0;
		r = (char*) he_StartHandlungSearch(2, 0, 0x1f, 3, *(int*) (productionBuilding + 1));
		while (r != 0) {
			for (sel = 0; sel < nslots; sel++) {
				((D2_CONTROL_TL*) (g_1015ea0))[slots[sel * 3 + 1]].value_1f4.bits = 0;
				if ((unsigned short) *(short*) (r + 0xb0) == slots[sel * 3]) {
					handle = slots[sel * 3 + 1];
					((D2_CONTROL_TL*) (g_1015ea0))[handle].value_05c = 0;
					fcn_0046f940(slots[sel * 3 + 2], *(int*) 0x14ab264);
					lo = (float) gm_GetElapsedMinutes(r + 0x44, r + 0x52);
					hi = (float) gm_GetElapsedMinutes(r + 0x44,
					                          (char*) 0x7f4c00);
					((D2_CONTROL_TL*) (g_1015ea0))[handle].value_1f4.real =
					    hi / lo;
					break;
				}
			}
			total++;
			r = (char*) he_fn_Handlung();
		}
		removed = 0;
		for (i = 0; i < nslots; i++) {
			if (fcn_00502cd0(*(int*) (productionBuilding + 0x5d), 1, 0, slots[i * 3]) != 0) {
				((D2_CONTROL_TL*) (g_1015ea0))[slots[i * 3 + 1]].value_05c = 0;
				fcn_0046f940(slots[i * 3 + 2], *(int*) 0x14ab268);
				removed++;
			}
		}
		d2_SetForm(han, 3);
		io_AppendText(0x17cf, productionBuilding,
		             (int) (unsigned char) *(base + 0x21) - total - removed,
		             0x17d4);
	} while (main_RunFrameLoop((void*) 0x5c2a40, 0x657c7) != 0);
	d2_DestroyForm(han);
}
