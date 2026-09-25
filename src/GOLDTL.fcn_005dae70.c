// FUNCTION: GOLD 0x005ce940
// SIZE: 352
// FUNCTION: GOLDTL 0x005dae70
// SIZE: 352

typedef struct
{
	int x0;
	char pad4[0x14];
} Law;
// SIZE 0x18

extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;
extern unsigned short g_7f4c04;

int __cdecl fcn_004e8a80(int, Law*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004e8240(int, int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005dae70(char* e)
{
	Law x;
	int r;
	int dlg;
	int id;
	int ok;
	int cancel;

	r = 0x22;
	if (e[2] != 6 && e[2] != 7) {
		return 0x20;
	}
	if (fcn_004e8a80(*(unsigned char*) (e + 0x166), &x) == 0) {
		return 0x40;
	}
	dlg = fcn_00470820(0, 0, "privillegien\\arbeiter_ausweisen");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1e24, (e[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (e + 0x166));
	id = fcn_00519190(0x1e25);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				fcn_004e8240(x.x0, 0, 0, g_7f4c04 > 13 ? 0xff : 3, 0xff);
				r = 0x90;
				g_774654 = 1;
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005dae70, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
