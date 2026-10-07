// FUNCTION: GOLDTL 0x005aa860

typedef struct
{
	int x0;
	int x4;
	char pad8[0xc];
} Req;
// SIZE 0x14

extern int g_772514;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern char s_6aaf90[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_004eba60(char*, Req*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005aa860(unsigned short* a1)
{
	Req s;
	int r;
	int dlg;
	int v;

	r = 0;
	dlg = fcn_00470820(0, 0, s_6aaf90);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x167c);
	fcn_004727a0(dlg, 2);
	if (g_7f4ca0[g_774970 * 540 + 9] == 0) {
		v = (unsigned char) g_7f4ca0[g_774970 * 540 + 0x169] + 0x253;
	} else {
		v = (unsigned char) g_7f4ca0[g_774970 * 540 + 0x169] + 0x27b;
	}
	fcn_00519190(0x167f, v, 8, *a1);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			s.x4 = *(int*) (a1 + 2);
			s.x0 = 1;
			fcn_004eba60(g_7f4ca0 + g_774970 * 540, &s);
			g_774654 = 3;
			r = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005aa860, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
