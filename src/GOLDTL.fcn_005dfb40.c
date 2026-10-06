// FUNCTION: GOLDTL 0x005dfb40

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
extern int g_772514;
extern int g_14ac654;
extern char* g_1015ea0;
extern char* g_77255c;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_14ce8d8;
extern int g_774654;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
int __cdecl fcn_005dfa40(int, int, Rec*);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005dfb40(int wait, int mode, int title, int a4, int a5, char* out)
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
	int n;
	int i;

	list = -1;
	field = -1;
	ok = -1;
	result = 0;
	dlg = fcn_00470820(0, 0, s_6acf98);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 2);
	fcn_00519190(title);
	fcn_004727a0(dlg, 0);
	fcn_00533f40(0x140, 0x100, g_772514, fcn_00472830(dlg, 1), 0x18, &w, &h, &field);
	memset(recs, 0, sizeof(recs));
	n = fcn_005dfa40(a4, a5, recs);
	flag = mode & 1;
	if (!flag) {
		fcn_004727a0(dlg, 3);
		ok = fcn_00472250(dlg, 3, fcn_00519190(0x1ccc));
		fcn_004727a0(dlg, 0);
		list = fcn_00472250(dlg, 0, 0);
		fcn_00472380(list, g_14ac654);
	}
	fcn_004727a0(dlg, 1);
	for (i = 0; i < n; i++) {
		recs[i].id = fcn_0046fac0(0, (short) (i * 24), recs[i].name, g_772514);
		((Slot*)g_1015ea0)[recs[i].id].f5c = 1;
		((Slot*)g_1015ea0)[recs[i].id].f6c = 1;
		((Slot*)g_1015ea0)[recs[i].id].f18 = ((Win*)g_77255c)->fc;
		((Slot*)g_1015ea0)[recs[i].id].f1d0 = 3;
	}
	_itoa(n, buf, 10);
	fcn_0046f940(field, buf);
	fcn_00472900(field, 0x54);
	while (fcn_005373e0((void*) fcn_005dfb40, wait) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0) {
			for (i = 0; i < n; i++) {
				if (g_67d370 == recs[i].id) {
					if (flag) {
						sprintf(out, s_6acf90, a4, recs[i].name, a5);
						g_774654 = 1;
						result = 1;
					} else {
						fcn_00472380(list, (int) recs[i].name);
					}
					break;
				}
			}
		}
		if (g_100f1dc != -1 && g_67d370 == ok) {
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
