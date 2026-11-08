typedef struct
{
	char pad0[0x5c];
	int x5c;
	char pad60[0x6c];
	char name[0x100];
	int x1cc;
	int x1d0;
	char pad1d4[0x2f4 - 0x1d4];
} Ctl;

extern int g_772514;
extern char* g_1015ea0;
extern char* g_14a5ad8[];
extern int g_100f1dc;
extern int g_67d370;
extern char g_7e23e3;
#include "client_dialog_state.h"
extern char s_6a3f8c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00469470(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0053cd40(void);
void __cdecl d2_UpdateRadioGroup(int);
char __cdecl fcn_00507400(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);
typedef struct
{
	char pad0[0x10];
	int x10;
	char pad14[0x240];
	int x254;
	int x258;
	char pad25c[0x3cc - 0x25c];
} Win;

extern int g_6a9b9c;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_774a3c;
extern int g_774a38;
extern char* g_779cb8;
extern char* g_14b5d58;

char* __cdecl fcn_004ce000(void);
char* __cdecl fcn_004ce040(void);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
char* __cdecl fcn_004ce190(int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_0046c310(int);

/* ADDRESS: GOLDTL 0x00593ff0 */
int __cdecl fcn_00593ff0(int a1)
{
	int grp;
	int r;
	int dlg;
	int types[11];
	int btns[11];
	int i;
	int t;
	int h;
	char* s;
	char* d;
	char c;

	r = 0;
	types[0] = 1;
	types[1] = 2;
	types[2] = 3;
	types[3] = 4;
	types[4] = 5;
	types[5] = 6;
	types[6] = 7;
	types[7] = 11;
	types[8] = 13;
	types[9] = 14;
	types[10] = 15;
	dlg = fcn_00470820(0, 0, s_6a3f8c);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	io_AppendText(0x1afa);
	grp = d2_CreateRadioGroup(0);
	for (i = 0; i < 11; i++) {
		t = types[i];
		h = fcn_0046f740(i % 3 * 96 + 100, (i / 3 + 1) * 80, t + 0x5a1, g_772514);
		btns[i] = h;
		((Ctl*)g_1015ea0)[h].x5c = 1;
		((Ctl*)g_1015ea0)[h].x1d0 = 3;
		s = g_14a5ad8[t];
		d = ((Ctl*)g_1015ea0)[h].name;
		do {
			c = *s++;
			*d++ = c;
		} while (c != 0);
		((Ctl*)g_1015ea0)[h].x1cc = 0x56;
		fcn_00469470(grp, h);
	}
	g_100f1dc = -1;
	while (fcn_005373e0((void*) fcn_0053cd40, a1) != 0) {
		d2_UpdateRadioGroup(grp);
		if (g_100f1dc != -1) {
			for (i = 0; i < 11; i++) {
				if (g_67d370 == btns[i]) {
					g_7e23e3 = fcn_00507400(types[i], 1);
					g_774654 = 1;
					r = 1;
					break;
				}
			}
		}
	}
	fcn_00469510(grp);
	fcn_00471e30(dlg);
	return r;
}

/* ADDRESS: GOLDTL 0x005941e0 */
void __cdecl fcn_005941e0(void)
{
	char buf[0x160];
	int last;
	int h;
	int n;
	char* e;
	char* p;

	last = -1;
	e = fcn_004ce000();
	d2_SetForm(g_6a9b9c, 5);
	h = ((Win*)g_1015f40)[g_772514].x254;
	io_AppendText((int) "$C");
	g_774a3c = 0;
	while (e != 0) {
		g_774a3c++;
		p = fcn_004ce190(*(int*) (e + 0x68));
		if (p != 0 && *(int*) p == *(int*) (e + 0x68)) {
			n = *(int*) (p + 0xc);
		} else {
			n = 9;
		}
		if (*(int*) (e + 0x64) != 0) {
			if ((((int*)g_779cb8) != 0 && *(int*) (e + 0x64) == *((int*)g_779cb8)) || *(int*) (e + 0x68) == *((int*)g_779cb8)) {
				sprintf(buf, "$%dFF%s (%s): %s$A", n, e + 0x40, g_14b5d58, e);
			}
		} else {
			sprintf(buf, "$%dFF%s: %s$A", n, e + 0x40, e);
		}
		last = io_AppendText((int) buf);
		e = fcn_004ce040();
	}
	if (g_774a3c > g_774a38 && last >= 0 && h > ((Win*)g_1015f40)[g_772514].x10) {
		g_774a38 = g_774a3c;
		n = h + 0x18;
		((Win*)g_1015f40)[g_772514].x254 = n;
		((Win*)g_1015f40)[g_772514].x258 = n - ((Win*)g_1015f40)[g_772514].x10;
		fcn_0046c310(g_772514);
	}
}
