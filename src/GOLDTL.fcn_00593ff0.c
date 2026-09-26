// FUNCTION: GOLDTL 0x00593ff0
// SIZE: 493

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
// SIZE 0x2f4

extern int g_772514;
extern char* g_1015ea0;
extern char* g_14a5ad8[];
extern int g_100f1dc;
extern int g_67d370;
extern char g_7e23e3;
extern int g_774654;
extern char s_6a3f8c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_004693b0(int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00469470(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0053cd40(void);
void __cdecl fcn_00469630(int);
char __cdecl fcn_00507400(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

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
	fcn_004727a0(dlg, 0);
	fcn_00519190(0x1afa);
	grp = fcn_004693b0(0);
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
		fcn_00469630(grp);
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
