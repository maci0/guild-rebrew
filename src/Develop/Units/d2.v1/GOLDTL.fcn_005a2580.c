#include <string.h>

/* Slot row passed to fcn_005ca560/fcn_005ca740. */
struct sel {
	char* who;           /* 0x00 */
	char pad4[0x0c];
	int x10;             /* 0x10 */
	int x14;             /* 0x14 */
	char pad18[0x18];
	int used;            /* 0x30 */
	char pad34[4];
};
// SIZE 0x38

/* Item record passed to fcn_004c5530. */
typedef struct Rec {
	char pad0[4];
	unsigned char kind;  /* 0x04 */
	char pad5[3];
	int x8;              /* 0x08 */
	int xc;              /* 0x0c */
	char pad10[0x18];
	int x28;             /* 0x28 */
	int x2c;             /* 0x2c */
	int x30;             /* 0x30 */
	short x34;           /* 0x34 */
	unsigned char x36;   /* 0x36 */
	char pad37[0x25];
	int x5c;             /* 0x5c */
	int x60;             /* 0x60 */
	char pad64[0x94];
} Rec;
/* SIZE 0xf8 */

extern int d2_CurrentWindowId;
extern char* g_772500;
extern char* g_77255c;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"
extern int d2_CurrentElementId;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_14ce8e0;
extern int g_100f1dc;
extern char g_7f4ca4[];

int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_SetForm(int h, int page);
void __cdecl fcn_005340f0(int a);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl fcn_004f7120(int id, char* rec, int* out1, int* out2, int* idx);
void __cdecl d2_ClearWindowChildren(int a, int b);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_BuildPersonStatusDesc(struct sel* s);
void __cdecl fcn_005ca740(int x, int y, int a, int b, struct sel* s, int c);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_005c91c0(char* buf, int x, int y, int a, int b);
char* __cdecl he_StartHandlungSearch(int a, int b, int c);
char* __cdecl he_fn_Handlung(void);
int __cdecl d2_GetWindowListItem(int h, int a, int b);
void __cdecl cm_SendCopyEntityData(Rec* r);
int __cdecl main_RunFrameLoop(void* fn, int id);
void __cdecl d2_DestroyForm(int h);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x005a2580 */
void __cdecl fcn_005a2580(char* a0, char* a1, char* a2)
{
	struct sel sel[3];
	Rec rec;
	char buf[512];
	int seen[3];
	char* fillDst;
	int vals[3];
	int idx[3];
	int h;
	int changed;
	int y;
	int x;
	int rc;
	int line;
	int found;
	int j;
	char* p;
	char* e;

	y = -1;
	seen[0] = -1;
	seen[1] = -1;
	seen[2] = -1;
	h = 0;
	vals[0] = 0;
	vals[1] = 0;
	vals[2] = 0;
	memset(sel, 0, sizeof(sel));
	h = fcn_00470820(0, 0, "locations\\Wirtshaus\\DUNKLEECKE");
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	memset(sel, 0, sizeof(sel));
	changed = 1;
	do {
		p = a2 + 0x1c;
		for (j = 0; j < 3; j++) {
			int out1;
			int out2;
			if (fcn_004f7120(*(int*) p, (*(unsigned short*) (a0 + 0x27)) * 540 + 0x7f4ca0,
				&out1, &out2, &idx[j])) {
				if (*(int*) p != seen[j]) {
					changed = 1;
				}
				sel[j].who = (char*) ((out2 & 0xffff) * 540 + 0x7f4ca0);
				seen[j] = *(int*) p;
				vals[j] = out1;
			} else if (seen[j] != -1) {
				changed = 1;
				sel[j].who = 0;
				seen[j] = -1;
				vals[j] = 0;
			}
			p += 4;
		}
		if (changed) {
			d2_SetForm(h, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText(0x18a3);
			x = *(int*) (g_77255c + 0xc) / 2;
			y = (x - *(short*) (g_772500 + 0x1ebd8)) - 0x28;
			for (j = 0, line = 0x46; line < 0x181; j++, line += 0x69) {
				sel[j].x10 = y;
				sel[j].x14 = line - 0x1e;
				sel[j].used = (sel[j].who != 0);
				d2_BuildPersonStatusDesc(&sel[j]);
				fcn_005ca740(sel[j].x10, sel[j].x14, d2_CurrentWindowId, 0x54, &sel[j], 1);
				if (seen[j] == -1) {
					io_FormatTextBuffer(buf, 0x18a6);
				} else {
					io_FormatTextBuffer(buf, 0x18a5, *(int*) (idx + j) * 5 + 0x13fd, vals[j]);
				}
				fcn_005c91c0(buf, x, line, 0xf0, 0x54);
			}
			changed = 0;
			found = 0;
			y = -1;
			for (e = he_StartHandlungSearch(1, 0, 0x74); e != 0; e = he_fn_Handlung()) {
				if (*(int*) (e + 0xb0) == *(int*) (a0 + 1)) {
					found = 1;
					break;
				}
			}
			d2_SetForm(h, 2);
			io_AppendText(0x6811b0);
			if (found) {
				io_AppendText(0x18a8);
			} else if (*(int*) (a2 + 0x28) < gm_GameTime) {
				rc = d2_GetWindowListItem(h, 2, io_AppendText(0x18a7));
				y = rc;
			}
		}
		if (g_100f1dc != -1 && d2_CurrentElementId == y) {
			int fillCount;
			fillDst = (char*) &rec;
			fillCount = sizeof(rec);
			__asm {
				mov edi, fillDst
				mov ebx, fillCount
				xor eax, eax
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short ItemFillTail
				rep stosb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep stosd
			ItemFillTail:
				add ecx, ebx
				rep stosb
			}
			rec.kind = 0x74;
			rec.x36 = 2;
			rec.x8 = *(int*) (g_7f4ca4 + (*(unsigned short*) &g_774970) * 540);
			rec.xc = *(int*) (a0 + 1);
			rec.x28 = gm_GameTime;
			rec.x2c = g_7f4c04;
			rec.x30 = g_7f4c08;
			rec.x34 = g_7f4c0c;
			rec.x5c = *(int*) (a0 + 1);
			rec.x60 = *(int*) (a1 + 2);
			cm_SendCopyEntityData(&rec);
			g_774654 = 1;
		} else if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(fcn_005a2580, 0x677c7) != 0);
	d2_DestroyForm(h);
}
#pragma optimize("", on)
