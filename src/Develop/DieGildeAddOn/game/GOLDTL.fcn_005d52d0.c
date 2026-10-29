#include "Develop/DieGildeAddOn/game/spiel.h"

extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;
extern unsigned char g_773d75;
extern double g_6660d8;
extern double g_664ee8;
extern double g_6629a0;
extern char g_6811b0[];

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c53a0(void);
int __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00525f60(void*, int);
int __cdecl fcn_00526010(void*, int, char);
int __cdecl gm_AccumulateTyped2(char*);

typedef struct {
	int sel;
	int mode;
	int n;
} DlgSel;

/* ADDRESS: GOLDTL 0x005d52d0 */
int __cdecl fcn_005d52d0(char* p)
{
	float w;
	DlgSel s;
	char* obj;
	int dlg;
	int m;
	int x;
	int base;

	s.sel = -1;
	s.mode = 0;
	if (*(unsigned char*) (p + 2) != 6 && *(unsigned char*) (p + 2) != 7) {
		if (*(int*) (p + 0x194) < 8) {
			return 0x22;
		}
		w = (float) gm_WalkEntityChain(*(unsigned short*) p);
		s.n = gm_AccumulateTyped2(p);
		if ((float) s.n / w < g_6660d8) {
			return 0x22;
		}
		obj = fcn_00508e40(*(int*) (p + 0x5c));
		fcn_004c6ae0(*(int*) (p + 4), -8);
		fcn_004c4510(p, *(int*) (p + 4));
		fcn_004c4700(4, 1, 0x5c, &s.sel);
		fcn_004c5360();
		fcn_004c4510(obj, *(int*) (obj + 4));
		fcn_004c4700(4, 1, 0x5c, &s.sel);
		fcn_004c4700(2, 1, 0x50, &s.sel);
		fcn_004c5360();
		m = (int) (w * g_664ee8);
		x = fcn_004c5150(*(int*) (obj + 4), *(int*) (p + 4), g_773d75, m);
		while (fcn_004c4450(x) == 0) {
			fcn_00535960();
		}
		return 0x11;
	}
	w = (float) gm_WalkEntityChain(*(unsigned short*) p);
	s.n = (int) (w * g_664ee8);
	obj = fcn_00508e40(*(int*) (p + 0x5c));
	dlg = fcn_00470820(0, 0, "privillegien\\scheidung");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	base = 0x114 + (*(unsigned char*) (p + 9) ? 0xa : 0);
	x = fcn_00519190(0x1d8f, base + *(unsigned char*) (p + 0xd), 8, s.n - (int) (w * g_6629a0), *(unsigned short*) obj, *(unsigned short*) obj);
	fcn_00472250(dlg, 1, x);
	fcn_00472250(dlg, 1, x + 1);
	g_100f1dc = -1;
	for (;;) {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (fcn_00525f60(p, 8) == 0 || fcn_00526010(p, s.n, g_773d75) == 0) {
					goto tail;
				}
				fcn_004c6ae0(*(int*) (p + 4), -8);
				fcn_004c4510(p, *(int*) (p + 4));
				fcn_004c4700(4, 1, 0x5c, &s.sel);
				x = fcn_004c53a0();
				while (fcn_004c4450(x) == 0) {
					fcn_00535960();
				}
				fcn_004c4510(obj, *(int*) (obj + 4));
				fcn_004c4700(4, 1, 0x5c, &s.sel);
				fcn_004c4700(2, 1, 0x50, &s.sel);
				x = fcn_004c53a0();
				while (fcn_004c4450(x) == 0) {
					fcn_00535960();
				}
				x = fcn_004c5150(*(int*) (obj + 4), *(int*) (p + 4), g_773d75, s.n);
				while (fcn_004c4450(x) == 0) {
					fcn_00535960();
				}
				fcn_00519190((int) g_6811b0);
				fcn_00519190(0x1d90);
				g_774654 = 1;
				s.mode = 0x81;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
				s.mode = 2;
			}
		}
tail:
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
			s.mode = 2;
		}
		if (fcn_005373e0(fcn_005d52d0, 0x657c7) == 0) {
			break;
		}
	}
	fcn_00471e30(dlg);
	return s.mode;
}
