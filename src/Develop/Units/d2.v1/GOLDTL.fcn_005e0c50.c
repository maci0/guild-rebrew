

#include <stdio.h>

// SIZE 0x210
typedef struct {
	char pad0[9];
	char name[0x80];
	char text[0x187];
} Rec;

// SIZE 0x220
typedef struct {
	char id;
	char pad1[3];
	int h;
	int f8;
	int padc;
	Rec rec;
} Slot;

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"








// SIZE 0x2f4
typedef struct {
	char pad0[0x10];
	int f10;
	int f14;
	char pad18[0x28];
	D2_WIN* f40;
	char pad44[0x2b0];
} Ctl;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char s_6acfdc[];
extern char s_6acfcc[];
extern char s_6acfb4[];
extern char s_6ad004[];
extern char* g_14ac648;
extern char g_773de8;

// SIZE 0x9600
typedef struct {
	int v[0x2580];
} Blob;

extern unsigned short ls_SavePreviewPixels[];
extern int d2_CurrentWindowId;
extern int main_LoopFlags;
extern int g_6b7fdc;
extern int d2_HoveredWindow;
extern char* g_14ac64c;
extern int g_14ce8e0;
extern int g_14ce8d8;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_005e0140(int, int, void*, void*, char*, int);
void __cdecl fcn_00472640(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl vfs_LookupPath(char*, int, int*);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl fcn_005e0b40(int, int, char*);
int __cdecl fcn_005dfe80(char*, int);
int __cdecl d2_OpenMessageBox(char*, int);
void __cdecl ls_SaveGame(char*, char*, int);
void __cdecl fcn_00471e30(int);

int __cdecl d2_RunSaveGameDialog(Blob* src)
{
	int i;
	int dlg;
	int sel;
	int wait;
	int b;
	int a;
	int c;
	int st;
	char tmp[0x104];
	char buf[0x104];
	Slot slots[16];
	Rec recs[32];
	int flag;
	int h;

	wait = main_LoopFlags;
	dlg = fcn_00470820(0, 0, s_6acfdc);
	fcn_00471db0(dlg, 1);
	fcn_00471d80(dlg, 2);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(0, 2);
	io_AppendText(0x1c58);
	d2_SetForm(0, 0);
	fcn_00533f40(0x214, 0x168, d2_CurrentWindowId, fcn_00472830(dlg, 1), 0x82, &a, &b, &c);
	fcn_005e0140(dlg, 1, slots, recs, s_6acfcc, 0);
	fcn_00472640(slots[0].h, 0);
	fcn_00472640(slots[1].h, 0);
	sel = fcn_00472830(dlg, 1);
	while (main_RunFrameLoop((void*) d2_RunSaveGameDialog, wait) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0 && *(int*) &((D2_WIN*)g_1015f40)[sel].pad3c[0x224] == 0) {
			for (i = 2; i < 16; i++) {
				if (d2_CurrentElementId != slots[i].h && d2_HoveredWindow != slots[i].f8) {
					if (d2_HoveredWindow == -1) {
						continue;
					}
					if (((Ctl*)g_1015ea0)[((D2_WIN*)g_1015f40)[d2_HoveredWindow].slot].f40 != &((D2_WIN*)g_1015f40)[slots[i].f8]) {
						continue;
					}
				}
				flag = 0;
				sprintf(tmp, s_6acfb4, slots[i].rec.name);
				if (vfs_LookupPath(tmp, g_6b7fdc, &st)) {
					flag = 1;
				}
				d2_SetSlotVisibility(slots[i].h, 0);
				if (!fcn_005e0b40(((Ctl*)g_1015ea0)[slots[i].h].f10, ((Ctl*)g_1015ea0)[slots[i].h].f14, slots[i].rec.text)) {
					d2_SetSlotVisibility(slots[i].h, 1);
					break;
				}
				if (!flag || fcn_005dfe80(g_14ac64c, 0x101)) {
					sprintf(buf, s_6ad004, i);
					(*(Blob*)ls_SavePreviewPixels) = *src;
					g_773de8 = (char) i;
					h = d2_OpenMessageBox(g_14ac648, 0);
					ls_SaveGame(buf, slots[i].rec.text, 1);
					fcn_00471e30(h);
					g_774654 = 1;
				}
				d2_SetSlotVisibility(slots[i].h, 1);
			}
		}
	}
	fcn_00471e30(dlg);
	return 0;
}
