#include <string.h>
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct F8 {
	int mask;
	int b;
} F8;

struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int f58;
	int f5c;
	int f60;
	int f64;
	int f68;
	int f6c;
	char pad70[0x88];
};

extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern pos14_7f4c00 gm_GameTime;
#include "GOLDTL.fcn_0058a250_gconf.h"
extern char g_7f4ca4[];

void* __cdecl fcn_005cd440(void*, char*, int, int);
int __cdecl fcn_004e99c0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, ...);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00525f60(char*, int);
int __cdecl fcn_005898f0(void*);
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004a5e60(unsigned short*, int, F8, int, float, int*);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* Builds the stock-trade dialog for the selected building, pumps the dialog
 * message loop and hands the scene back to the shared frame function. */
/* ADDRESS: GOLDTL 0x0058a250 */
void __cdecl d2_RunSpyCabinetDialog(int a0)
{
	int ids[3];
	int q[20];
	struct msg req;
	char* targetEntity;
	int dlg;
	int elem;
	int confirmButton;
	int cancelButton;
	int v16;
	int sel;
	int id;
	int i;
	int n; int cost;
	F8 f; char *linkedObject;

	for (i = 0; i < 20; i++) {
		q[i] = 0;
	}
	for (i = 7; i < 15; i++) {
		q[i] = -1;
	}
	q[0] = 1;
	q[1] = 0x400;
	q[4] = 6;
	targetEntity = (char*) fcn_005cd440(q, (char*) *(int*) 0x14b5310, 0, 0);
	if (targetEntity == 0) {
		fcn_00532ef0();
		return;
	}
	n = fcn_004e99c0(*(unsigned char*) (targetEntity + 0x166)) / 3 + 2;
	ids[0] = n + 3;
	ids[1] = n + 5;
	ids[2] = n + 8;
	dlg = fcn_00470820(0, 0, (char*) 0x6a9514);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 2);
	elem = d2_ShowTxt(0, 3, (char*) *(int*) 0x14b531c, d2_CurrentWindowId);
	*(int*) (elem * 0x2f4 + (int) g_1015ea0 + 0x6c) = 1;
	*(int*) (elem * 0x2f4 + (int) g_1015ea0 + 0x18) = *(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c);
	d2_SetElementFont(elem, 0x54);
	elem = fcn_004677e0(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 2, d2_CurrentWindowId);
	d2_SetElementValue(elem, 0, 2, 0, 1);
	fcn_00468bb0(elem, 3, *(int*) 0x14b5320, *(int*) 0x14b5324, *(int*) 0x14b5328);
	d2_SetForm(dlg, 3);
	v16 = io_AppendText(0x4003);
	confirmButton = fcn_00472250(dlg, 3, v16);
	cancelButton = fcn_00472250(dlg, 3, v16 + 1);
	g_100f1dc = -1;
	do {
		sel = fcn_00471f80(elem);
		v16 = sel;
		d2_SetForm(dlg, 1);
		io_AppendText(0x6811b0);
		io_AppendText(0x3ffd, 0x3ffb, *(unsigned short*) targetEntity, n);
		cost = ids[sel]; io_AppendText(0x3ffe, cost);
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == confirmButton) {
				if (fcn_00525f60(g_slot_table + g_774970 * 0x21c, cost) == 1 && fcn_005898f0((void*) a0) != 0) {
					fcn_005100f0(*(int*) (g_slot_table + g_774970 * 0x21c + 4), -cost);
					memset(&req, 0, sizeof(req));
					req.kind = 0x99;
					req.code = 2;
					req.f64 = -1;
					req.f68 = 1;
					req.owner = *(int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + (int) g_7f4ca4);
					req.when = gm_GameTime;
					req.target = *(int*) (a0 + 1);
					req.f5c = *(int*) (a0 + 1);
					linkedObject = *(char**) (targetEntity + 0x170);
					req.f60 = *(int*) (targetEntity + 4);
					req.f6c = v16;
					if (linkedObject != 0) {
						req.f58 = *(int*) (linkedObject + 1);
					} else if (*(int*) (targetEntity + 0x16c) != 0) {
						req.f58 = *(int*) (*(int*) (targetEntity + 0x16c) + 1);
					} else {
						v16 = -1;
						f.mask = 0x7b4c4a0;
						f.b = 0;
						fcn_004a5e60((unsigned short*) (g_slot_table + g_774970 * 0x21c), 0, f, 0, 100.0f, &v16);
						req.f58 = v16;
					}
					id = fcn_004c5530(&req);
					while (id != -1 && fcn_004c4450(id) == 0) {
						fcn_005373e0(0, 0x20007);
					}
					fcn_004c3030(-7, 0, (char*) 0x6a9508, 0);
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == cancelButton) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) d2_RunSpyCabinetDialog, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
