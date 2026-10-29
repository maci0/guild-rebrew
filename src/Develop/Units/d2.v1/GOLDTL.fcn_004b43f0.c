extern int g_67d370;
extern int g_7e46ac;
extern int g_100f1dc;
extern int g_774654;
extern signed char g_6a3440;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_004695a0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
int __cdecl fcn_004b3fe0(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_004b41b0(void);

/* ADDRESS: GOLDTL 0x004b43f0 */
int __cdecl fcn_004b43f0(int n)
{
	int b0;
	int b1;
	int b2;
	int b3;
	int b4;
	int b5;
	int b6;
	int list;
	int dlg;
	int base;
	int sel;
	int r;

	r = 0;
	dlg = fcn_00470820(0, 0, "Menu\\CHOOSEHISTORY");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	base = fcn_00519190(0x1b9f);
	b0 = fcn_00472250(dlg, 0, base);
	b1 = fcn_00472250(dlg, 0, base + 1);
	b2 = fcn_00472250(dlg, 0, base + 2);
	b3 = fcn_00472250(dlg, 0, base + 3);
	b4 = fcn_00472250(dlg, 0, base + 4);
	b5 = fcn_00472250(dlg, 0, base + 5);
	b6 = fcn_00472250(dlg, 0, base + 6);
	list = d2_CreateRadioGroup(7, b0, b1, b2, b3, b4, b5, b6);
	sel = 1;
	if (n > 0) {
		fcn_00472640(b1, 0);
		sel = 2;
	}
	if (n > 1) {
		fcn_00472640(b2, 0);
		sel++;
	}
	if (n > 2) {
		fcn_00472640(b3, 0);
		sel++;
	}
	if (n > 3) {
		fcn_00472640(b4, 0);
		sel++;
	}
	if (n > 4) {
		fcn_00472640(b5, 0);
		sel = 0;
	}
	fcn_004695a0(list, sel);
	if (fcn_005373e0(fcn_004b41b0, g_7e46ac) != 0) {
		do {
			fcn_00469630(list);
			if (g_100f1dc == 2) {
				if (g_67d370 == b6) {
					g_6a3440 = -1;
					r = 0xff;
					g_774654 = 1;
				} else if (g_67d370 == b0) {
					g_6a3440 = -1;
					r = 0;
					g_774654 = 1;
				} else {
					if (g_67d370 == b1) {
						g_6a3440 = 0;
					} else if (g_67d370 == b2) {
						g_6a3440 = 1;
					} else if (g_67d370 == b3) {
						g_6a3440 = 2;
					} else if (g_67d370 == b4) {
						g_6a3440 = 3;
					} else if (g_67d370 == b5) {
						g_6a3440 = 4;
					}
					fcn_004695a0(list, 0);
					r = fcn_004b3fe0(g_6a3440);
					if (r != 0 && r != 0xff) {
						g_774654 = 1;
					}
				}
			}
		} while (fcn_005373e0(fcn_004b41b0, g_7e46ac) != 0);
	}
	fcn_00469510(list);
	fcn_00471e30(dlg);
	return r;
}
