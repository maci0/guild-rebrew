// FUNCTION: GOLDTL 0x0058c670
// SIZE: 272

extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;

int __cdecl fcn_00470820(int, int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004f2a10(int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0058c670(int a1, int a2, unsigned char a3)
{
	int dlg;
	int id;
	int ok;
	int cancel;
	int r;

	r = 0;
	dlg = fcn_00470820(0, 0, 0x6a96d8);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x410f, 0x410e);
	fcn_004727a0(dlg, 2);
	id = fcn_00519190(0x4111);
	ok = fcn_00472250(dlg, 2, id);
	cancel = fcn_00472250(dlg, 2, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				fcn_004f2a10(0, a1, a2, a3);
				r = 1;
				g_774654 = 1;
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_0058c670, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
