

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

extern int g_7e46ac;
extern unsigned char g_773d75;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_100f1dc;
extern int g_774654;
extern char g_14cf950;
extern int g_14abbf4;
extern int g_14ce8e0;
extern char s_68d704[];

int __cdecl fcn_00526010(Player*, int, char);
int __cdecl fcn_00470820(int, int, char*);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl gm_AccumulateTyped2(Player*);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00471b60(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005b5750(void)
{
	int timer;
	int r;
	int dlg;
	int ctl;
	int v;

	r = 0;
	timer = g_7e46ac;
	if (fcn_00526010(&((Player*)g_7f4ca0)[g_774970], 0x140, (*(char*)&g_773d75)) == 0) {
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_68d704);
	ctl = fcn_00472250(dlg, 0, io_AppendText(0x1a34, (unsigned char) (*(char*)&g_773d75)));
	v = gm_AccumulateTyped2(&((Player*)g_7f4ca0)[g_774970]);
	if (v >= 0x12c0) {
		v = 0x12c0;
	}
	d2_SetElementValue(ctl, 0xa, v / 32, 0xa);
	fcn_00471b60(dlg);
	if (fcn_005373e0((void*) fcn_005b5750, timer) != 0) {
		do {
			if (g_100f1dc != 2) {
				if (g_100f1dc == 1 || g_14cf950 == 1) {
					g_774654 = 1;
					r = 0;
				}
			}
			else {
				fcn_00526120(g_14abbf4, 4);
				g_774654 = 1;
				r = fcn_00471f80(ctl);
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005b5750, timer) != 0);
	}
	fcn_00471e30(dlg);
	return r;
}
