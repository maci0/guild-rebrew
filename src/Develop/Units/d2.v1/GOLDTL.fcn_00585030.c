// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int x18;
	char pad1c[0x40];
	int x5c;
	char pad60[0xc];
	int x6c;
	char pad70[0x280];
	int x2f0;
} Ctl;

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int xc;
	char pad10[0x3cc - 0x10];
} Screen;

extern int g_6b7fac;
extern int g_772514;
extern char* g_77255c;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern int g_14b546c;
extern int g_14b5470;
extern int g_14b59e0;
extern char* lpObjektePROT;
extern float g_662cf8;
extern float g_66413c;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern List8c_102cbc8 g_102cbc8[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00469630(int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void* __cdecl fcn_004ec7d0(unsigned char*);
int __cdecl fcn_004ecf00(char*, int*, float*, int);
int __cdecl fcn_004ecc20(int);
int __cdecl fcn_00585760(char*, int*, int);
int __cdecl fcn_00585850(char*, int*);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_00532ef0(void);

#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00585030 */
void __cdecl fcn_00585030(int a0)
{
	char* e;
	char* data;
	int* src;
	int* ids;
	int items[6];
	int two[2];
	char buf[0x100];
	char buf2[0x100];
	int owner;
	float frac;
	int win;
	int wnd;
	int list;
	int sel;
	int prev;
	int stamp;
	int count;
	int i;
	int x;
	int y;
	int item;
	int dlg;
	int flag;

	e = (char*) a0;
	data = fcn_004ec7d0((unsigned char*) a0);
	src = *(int**) (e + 0x65);
	sel = fcn_004ecf00(e, &owner, &frac, 0);
	stamp = g_6b7fac;
	g_100f1dc = -1;
	win = fcn_00470820(0, 0, "Locations\\Domizil\\Alchemistry2");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(win);
	d2_SetForm(win, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(win, 2);
	wnd = g_772514;
	d2_SetForm(win, 1);
	io_AppendText(0x404f);
	if (data == 0) {
		d2_SetForm(win, 2);
		io_AppendText(0x4051, 0x182);
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_00585030, 0x677c7) != 0);
		fcn_00471e30(win);
		return;
	}
	d2_SetForm(win, 3);
	fcn_00533a60(g_772514, 0, two, 2, g_14b546c, g_14b5470);
	prev = sel;
	d2_SetForm(win, 2);
	io_AppendText(0x6811b0);
	list = d2_CreateRadioGroup(0);
	count = 0;
	ids = items;
	src = (int*) ((int) *(int**) (e + 0x65) + 0xc);
	for (i = 0; i < 6; i++, src += 2) {
		if (src[0] == 0) {
			continue;
		}
		x = (count & 1) * 0xf0;
		y = (count / 2) * 0x50;
		item = fcn_0046f740(x + 10, y + 10, src[0] + 0xdf, wnd);
		*ids++ = item;
		((Ctl*) g_1015ea0)[item].x5c = 1;
		((Ctl*) g_1015ea0)[item].x2f0 = (int) (lpObjektePROT + src[0] * 0x41);
		fcn_00469470(list, item);
		io_FormatTextBuffer(buf, (char*) 0x679060, src[0] * 2 + 0x9a8);
		item = d2_ShowTxt(x + 0x3c, y + 5, buf, wnd);
		((Ctl*) g_1015ea0)[item].x18 = g_1015f40[wnd].xc / 2 - 10;
		fcn_00472900(item, 0x54);
		fcn_00534160(x + 0x3c, y + 0x19, (int) (*(float*) (src + 1) * g_66413c), 0x4df);
		count++;
	}
	do {
		sel = fcn_004ecf00(e, &owner, &frac, 0);
		d2_SetForm(win, 4);
		io_AppendText(0x6811b0);
		if (sel != 0) {
			dlg = fcn_004677e0((((Screen*) g_77255c)->xc - 0x12c) / 2, 0x12, 0x12c, 0, 0x64, 0x75, 0x42, g_772514);
			if (sel == 1) {
				io_FormatTextBuffer(buf, (char*) 0x404b);
			} else if (sel == 2) {
				io_FormatTextBuffer(buf, (char*) 0x404c, owner * 2 + 0x9a8);
			} else if (sel == 3) {
				io_FormatTextBuffer(buf, (char*) 0x404d, owner + 0x4172);
			}
			item = d2_ShowTxt(0, 0, buf, g_772514);
			((Ctl*) g_1015ea0)[item].x18 = ((Screen*) g_77255c)->xc;
			((Ctl*) g_1015ea0)[item].x6c = 1;
			fcn_00472900(item, 0x54);
			d2_SetElementValue(dlg, 0, 0x64, (int) (frac * g_662cf8));
		}
		flag = 0;
		if (g_102cbc8[list].n != -1 && count != 0 && sel == 0) {
			flag = 1;
		}
		fcn_00472640(two[1], flag);
		fcn_00472640(two[0], sel == 0);
		if (sel != prev || g_6b7fac > (unsigned int) (stamp + 0x32)) {
			stamp = g_6b7fac;
			prev = sel;
			owner = g_102cbc8[list].n;
			fcn_00469510(list);
			d2_SetForm(win, 2);
			io_AppendText(0x6811b0);
			list = d2_CreateRadioGroup(0);
			count = 0;
			ids = items;
			src = (int*) ((int) *(int**) (e + 0x65) + 0xc);
			for (i = 0; i < 6; i++, src += 2) {
				if (src[0] == 0) {
					continue;
				}
				x = (count & 1) * 0xf0;
				y = (count / 2) * 0x50;
				item = fcn_0046f740(x + 10, y + 10, src[0] + 0xdf, wnd);
				*ids++ = item;
				((Ctl*) g_1015ea0)[item].x5c = 1;
				((Ctl*) g_1015ea0)[item].x2f0 = (int) (lpObjektePROT + src[0] * 0x41);
				fcn_00469470(list, item);
				io_FormatTextBuffer(buf2, (char*) 0x679060, src[0] * 2 + 0x9a8);
				item = d2_ShowTxt(x + 0x3c, y + 5, buf2, wnd);
				((Ctl*) g_1015ea0)[item].x18 = g_1015f40[wnd].xc / 2 - 10;
				fcn_00472900(item, 0x54);
				fcn_00534160(x + 0x3c, y + 0x19, (int) (*(float*) (src + 1) * g_66413c), 0x4df);
				count++;
			}
			g_102cbc8[list].n = owner;
			fcn_00469630(list);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == two[1]) {
				for (i = 0; i < 6; i++) {
					if (g_102cbc8[list].n != i) {
						continue;
					}
					if (fcn_004ecc20((int) data) != 0) {
						fcn_00585760(e, *(int**) (e + 0x65), i);
					} else {
						fcn_00526120(g_14b59e0, 0);
					}
				}
			} else if (g_67d370 == two[0]) {
				fcn_00585850(e, *(int**) (e + 0x65));
			}
		}
	} while (fcn_005373e0((void*) fcn_00585030, 0x677c7) != 0);
	fcn_00469510(list);
	fcn_00471e30(win);
	fcn_00532ef0();
}
