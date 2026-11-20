

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SIZE 0x210
typedef struct {
	int id;
	char pad4[5];
	char name[0x207];
} Rec;

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int f18;
	char pad1c[0x40];
	int f5c;
	char pad60[0xc];
	int f6c;
	char pad70[0x160];
	int f1d0;
	char pad1d4[0x120];
} Slot;

// SIZE 0x10
typedef struct {
	char pad0[0xc];
	int fc;
} Win;

extern char s_6acf98[];
extern char s_6acf90[];
extern int d2_CurrentWindowId;
extern char* g_14ac654;
extern char* g_1015ea0;
extern char* g_77255c;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_14ce8d8;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
int __cdecl vfs_ListFilesByExtension(int, int, Rec*);
int __cdecl fcn_00472250(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_0046f940(int, char*);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl d2_OpenFileSelector(int wait, int mode, int title, int a4, int a5, char* out)
{
	int list;
	int field;
	int result;
	int flag;
	int ok;
	int w;
	int h;
	char buf[0x20];
	Rec recs[32];
	int dlg;
	int count;
	int i;

	list = -1;
	field = -1;
	ok = -1;
	result = 0;
	dlg = fcn_00470820(0, 0, s_6acf98);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 2);
	io_AppendText(title);
	d2_SetForm(dlg, 0);
	fcn_00533f40(0x140, 0x100, d2_CurrentWindowId, fcn_00472830(dlg, 1), 0x18, &w, &h, &field);
	memset(recs, 0, sizeof(recs));
	count = vfs_ListFilesByExtension(a4, a5, recs);
	flag = mode & 1;
	if (!flag) {
		d2_SetForm(dlg, 3);
		ok = fcn_00472250(dlg, 3, io_AppendText(0x1ccc));
		d2_SetForm(dlg, 0);
		list = fcn_00472250(dlg, 0, 0);
		d2_SetElementValue(list, g_14ac654);
	}
	d2_SetForm(dlg, 1);
	for (i = 0; i < count; i++) {
		recs[i].id = d2_ShowTxt(0, (short) (i * 24), recs[i].name, d2_CurrentWindowId);
		((D2_CONTROL_TL*) g_1015ea0)[recs[i].id].value_05c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[recs[i].id].value_06c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[recs[i].id].width = ((Win*)g_77255c)->fc;
		((D2_CONTROL_TL*) g_1015ea0)[recs[i].id].flags_1d0 = 3;
	}
	_itoa(count, buf, 10);
	fcn_0046f940(field, buf);
	d2_SetElementFont(field, 0x54);
	while (fcn_005373e0((void*) d2_OpenFileSelector, wait) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0) {
			for (i = 0; i < count; i++) {
				if (d2_CurrentElementId == recs[i].id) {
					if (flag) {
						sprintf(out, s_6acf90, a4, recs[i].name, a5);
						g_774654 = 1;
						result = 1;
					} else {
						d2_SetElementValue(list, recs[i].name);
					}
					break;
				}
			}
		}
		if (g_100f1dc != -1 && d2_CurrentElementId == ok) {
			if (!flag) {
				sprintf(out, s_6acf90, a4, fcn_00471f80(list), a5);
			}
			g_774654 = 1;
			result = 1;
		}
	}
	fcn_00471e30(dlg);
	return result;
}
