


extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;

int __cdecl fcn_004f5e20(int, int);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00525f60(char*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d8e30(char* e, char* o)
{
	int ok;
	int cancel;
	int sl;
	char buf[0x100];
	int n;
	int r;
	int dlg;
	int id;
	int v;

	if (e[2] != 6) {
		n = *(int*) (o + 4);
		if (n < 1 || n > 9 || n > *(int*) (e + 0x194)) {
			return 0x60;
		}
		fcn_004f5e20(*(int*) (e + 4), n);
		fcn_004c6ae0(*(int*) (e + 4), -*(int*) (o + 4));
	}
	if (e[2] == 6) {
		r = 0;
		dlg = fcn_00470820(0, 0, "privillegien\\abbitte");
		d2_SetOverlayAnimation(0, 0);
		fcn_00471b60(dlg);
		d2_SetForm(dlg, 1);
		id = io_AppendText(0x1dea);
		ok = fcn_00472250(dlg, 1, id + 1);
		cancel = fcn_00472250(dlg, 1, id + 2);
		sl = fcn_00472250(dlg, 1, id);
		d2_SetElementValue(sl, 1, 9, 1);
		g_100f1dc = -1;
		do {
			if (g_100f1dc != -1) {
				if (g_67d370 == ok) {
					v = fcn_00471f80(sl);
					if (fcn_00525f60(e, v) != 0) {
						fcn_004c6ae0(*(int*) (e + 4), -v);
						io_FormatTextBuffer(buf, 0x1deb, fcn_004f5e20(*(int*) (e + 4), v));
						fcn_00526120(buf, 0);
						r = 1;
						g_774654 = 1;
					}
				} else if (g_67d370 == cancel) {
					g_774654 = 1;
				}
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005d8e30, 0x657c7) != 0);
		fcn_00471e30(dlg);
		return r;
	}
	return 0;
}
